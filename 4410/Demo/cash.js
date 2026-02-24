
/* CSCI 4410/5410 OLA3 v2 Demo
   Grocery scan app: camera scan (ZXing) -> inventory lookup -> cart -> total
*/

"use strict";

/** ---------- Utilities ---------- */
function formatMoney(amount) {
  const n = Number(amount);
  if (Number.isNaN(n)) return "$0.00";
  return `$${n.toFixed(2)}`;
}

function safeParsePrice(v) {
  const n = parseFloat(v);
  return Number.isFinite(n) ? n : NaN;
}

/** ---------- Global State ---------- */
let inventory = {};
let inventoryLoaded = false;

let codeReader = null;
let scanning = false;
let lastScanAt = 0;

// This object holds the "currently scanned item preview"
let currentScanned = null;

/** ---------- cashRegister object ---------- */
const cashRegister = {
  cart: [], // [{ code, name, price, qty }]
  total: 0,

  addItem(item) {
    // item: {code, name, price}
    const idx = this.cart.findIndex(x => x.code === item.code);
    if (idx >= 0) {
      this.cart[idx].qty += 1;
    } else {
      this.cart.push({ ...item, qty: 1 });
    }
    this.recalculateTotal();
  },

  increaseQty(code) {
    const found = this.cart.find(x => x.code === code);
    if (!found) return;
    found.qty += 1;
    this.recalculateTotal();
  },

  decreaseQty(code) {
    const found = this.cart.find(x => x.code === code);
    if (!found) return;
    found.qty -= 1;
    if (found.qty <= 0) {
      this.cart = this.cart.filter(x => x.code !== code);
    }
    this.recalculateTotal();
  },

  removeItem(code) {
    this.cart = this.cart.filter(x => x.code !== code);
    this.recalculateTotal();
  },

  recalculateTotal() {
    let sum = 0;
    let count = 0;
    for (const item of this.cart) {
      sum += item.price * item.qty;
      count += item.qty;
    }
    this.total = sum;
    updateTotalsUI(count, sum);
    renderCart();
  },

  reset() {
    this.cart = [];
    this.total = 0;
    this.recalculateTotal();
  }
};

/** ---------- DOM Elements ---------- */
const el = {
  invStatus: document.getElementById("invStatus"),
  lastCode: document.getElementById("lastCode"),
  lastFormat: document.getElementById("lastFormat"),
  itemPreview: document.getElementById("itemPreview"),

  startScan: document.getElementById("startScan"),
  stopScan: document.getElementById("stopScan"),
  addToCart: document.getElementById("addToCart"),
  resetAll: document.getElementById("resetAll"),

  cartList: document.getElementById("cartList"),
  itemCount: document.getElementById("itemCount"),
  totalDisplay: document.getElementById("totalDisplay"),

  previewVideo: document.getElementById("preview"),

  unknownBox: document.getElementById("unknownBox"),
  unknownName: document.getElementById("unknownName"),
  unknownPrice: document.getElementById("unknownPrice"),
  saveUnknown: document.getElementById("saveUnknown"),
  cancelUnknown: document.getElementById("cancelUnknown")
};

/** ---------- Inventory Loading ---------- */
async function loadInventory() {
  try {
    const res = await fetch("inventory.json", { cache: "no-store" });
    if (!res.ok) throw new Error(`Failed to load inventory.json (HTTP ${res.status})`);
    inventory = await res.json();
    inventoryLoaded = true;
    el.invStatus.textContent = "Yes";
  } catch (err) {
    console.error(err);
    inventory = {};
    inventoryLoaded = false;
    el.invStatus.textContent = "No (inventory.json missing?)";
  }
}

/** ---------- UI Updates ---------- */
function setPreviewMessage(msg, muted = true) {
  el.itemPreview.textContent = msg;
  el.itemPreview.classList.toggle("muted", muted);
}

function showUnknownBox(show) {
  el.unknownBox.classList.toggle("hidden", !show);
  if (show) {
    el.unknownName.value = "";
    el.unknownPrice.value = "";
    el.unknownName.focus();
  }
}

function updateTotalsUI(count, total) {
  el.itemCount.textContent = String(count);
  el.totalDisplay.textContent = formatMoney(total);
}

function renderCart() {
  el.cartList.innerHTML = "";

  if (cashRegister.cart.length === 0) {
    const empty = document.createElement("li");
    empty.className = "muted";
    empty.textContent = "Cart is empty. Scan an item to add it.";
    el.cartList.appendChild(empty);
    return;
  }

  for (const item of cashRegister.cart) {
    const li = document.createElement("li");
    li.className = "cart-item";

    const top = document.createElement("div");
    top.className = "cart-top";

    const left = document.createElement("div");
    const name = document.createElement("div");
    name.className = "cart-name";
    name.textContent = item.name;

    const meta = document.createElement("div");
    meta.className = "cart-meta";
    meta.textContent = `Code: ${item.code} • Unit: ${formatMoney(item.price)} • Subtotal: ${formatMoney(item.price * item.qty)}`;

    left.appendChild(name);
    left.appendChild(meta);

    const right = document.createElement("div");
    right.className = "mono";
    right.textContent = `x${item.qty}`;

    top.appendChild(left);
    top.appendChild(right);

    const controls = document.createElement("div");
    controls.className = "cart-controls";

    const btnMinus = document.createElement("button");
    btnMinus.className = "btn small";
    btnMinus.textContent = "−";
    btnMinus.addEventListener("click", () => cashRegister.decreaseQty(item.code));

    const qty = document.createElement("span");
    qty.className = "qty";
    qty.textContent = String(item.qty);

    const btnPlus = document.createElement("button");
    btnPlus.className = "btn small";
    btnPlus.textContent = "+";
    btnPlus.addEventListener("click", () => cashRegister.increaseQty(item.code));

    const btnRemove = document.createElement("button");
    btnRemove.className = "btn small danger";
    btnRemove.textContent = "Remove";
    btnRemove.addEventListener("click", () => cashRegister.removeItem(item.code));

    controls.appendChild(btnMinus);
    controls.appendChild(qty);
    controls.appendChild(btnPlus);
    controls.appendChild(btnRemove);

    li.appendChild(top);
    li.appendChild(controls);
    el.cartList.appendChild(li);
  }
}

/** ---------- Scanner Logic (ZXing) ---------- */

async function startCameraScan() {
  if (!window.ZXing) {
    alert("ZXing library not loaded. Check your internet connection.");
    return;
  }
  if (!navigator.mediaDevices || !navigator.mediaDevices.getUserMedia) {
    alert("Camera API not supported in this browser. Try Chrome/Safari on mobile.");
    return;
  }
  if (scanning) return;

  scanning = true;
  el.startScan.disabled = true;
  el.stopScan.disabled = false;

  // 1) Request permission FIRST (critical for some browsers)
  let tempStream = null;
  try {
    tempStream = await navigator.mediaDevices.getUserMedia({
      video: { facingMode: "environment" },
      audio: false
    });
  } catch (err) {
    console.error(err);
    alert("Camera permission denied or unavailable. Please allow camera access and try again.");
    stopCameraScan();
    return;
  } finally {
    // stop the temp stream immediately (we only needed permission)
    if (tempStream) tempStream.getTracks().forEach(t => t.stop());
  }

  // 2) Now list devices and start ZXing
  codeReader = new ZXing.BrowserMultiFormatReader();

  let devices = [];
  try {
    devices = await ZXing.BrowserCodeReader.listVideoInputDevices();
  } catch (err) {
    console.error(err);
    alert("Could not access cameras. Try Safari/Chrome (not an in-app browser) and refresh.");
    stopCameraScan();
    return;
  }

  if (!devices.length) {
    alert("No camera found. Try a phone (rear camera works best).");
    stopCameraScan();
    return;
  }

  const preferredDeviceId =
    devices.find(d => /back|rear|environment/i.test(d.label))?.deviceId || devices[0].deviceId;

  try {
    await codeReader.decodeFromVideoDevice(
      preferredDeviceId,
      el.previewVideo,
      (result, err) => {
        if (result) handleScanResult(result);
      }
    );
  } catch (err) {
    console.error(err);
    alert("Failed to start camera scanning. Try another browser or device.");
    stopCameraScan();
  }
}



////


function stopCameraScan() {
  scanning = false;

  el.startScan.disabled = false;
  el.stopScan.disabled = true;

  if (codeReader) {
    try { codeReader.reset(); } catch (_) {}
    codeReader = null;
  }
}

function handleScanResult(result) {
  // Debounce: avoid repeated scans of the same code multiple times per second
  const now = Date.now();
  if (now - lastScanAt < 1100) return; // ~1.1 seconds
  lastScanAt = now;

  const code = result.getText();
  const format = (result.getBarcodeFormat && result.getBarcodeFormat()) ? String(result.getBarcodeFormat()) : "Unknown";

  el.lastCode.textContent = code;
  el.lastFormat.textContent = format;

  // Lookup in inventory.json
  const hit = inventory[code];

  if (hit && typeof hit.price === "number") {
    currentScanned = { code, name: hit.name || "Unnamed Item", price: hit.price };
    setPreviewMessage(`${currentScanned.name}\nUnit Price: ${formatMoney(currentScanned.price)}`, false);
    el.addToCart.disabled = false;
    showUnknownBox(false);
  } else {
    // Not found
    currentScanned = { code, name: "Unknown item", price: NaN };
    setPreviewMessage(`Unknown item\nCode: ${code}\nEnter name and price to add.`, true);
    el.addToCart.disabled = true;
    showUnknownBox(true);
  }
}

/** ---------- Actions ---------- */
function addCurrentToCart() {
  if (!currentScanned) return;
  if (!Number.isFinite(currentScanned.price)) return;

  cashRegister.addItem({
    code: currentScanned.code,
    name: currentScanned.name,
    price: currentScanned.price
  });

  // Optional UX: disable add until next scan
  el.addToCart.disabled = true;
  setPreviewMessage("Added to cart. Scan another item.", true);
}

function saveUnknownAndAdd() {
  if (!currentScanned) return;

  const name = el.unknownName.value.trim();
  const price = safeParsePrice(el.unknownPrice.value);

  if (!name) {
    alert("Please enter an item name.");
    el.unknownName.focus();
    return;
  }
  if (!Number.isFinite(price)) {
    alert("Please enter a valid price.");
    el.unknownPrice.focus();
    return;
  }

  const item = { code: currentScanned.code, name, price };

  // Add to cart
  cashRegister.addItem(item);

  // Optionally remember it in memory for this session
  inventory[item.code] = { name: item.name, price: item.price };

  // Update preview
  currentScanned = item;
  setPreviewMessage(`${item.name}\nUnit Price: ${formatMoney(item.price)}`, false);
  el.addToCart.disabled = false;

  showUnknownBox(false);
}

function cancelUnknown() {
  showUnknownBox(false);
  currentScanned = null;
  el.addToCart.disabled = true;
  setPreviewMessage("Scan an item to preview details here.", true);
}

function resetAll() {
  stopCameraScan();

  cashRegister.reset();

  currentScanned = null;
  el.lastCode.textContent = "None";
  el.lastFormat.textContent = "—";
  el.addToCart.disabled = true;
  showUnknownBox(false);
  setPreviewMessage("Scan an item to preview details here.", true);
}

/** ---------- Event Listeners ---------- */
el.startScan.addEventListener("click", startCameraScan);
el.stopScan.addEventListener("click", stopCameraScan);
el.addToCart.addEventListener("click", addCurrentToCart);
el.resetAll.addEventListener("click", resetAll);

el.saveUnknown.addEventListener("click", saveUnknownAndAdd);
el.cancelUnknown.addEventListener("click", cancelUnknown);

/** ---------- Init ---------- */
(async function init() {
  setPreviewMessage("Scan an item to preview details here.", true);
  updateTotalsUI(0, 0);
  renderCart();
  await loadInventory();
})();
