
// ===========================================
// Infinity Academy
// script.js
// ===========================================

// Fade in page
window.addEventListener("load", () => {
    document.body.classList.add("loaded");
});

// Smooth scrolling for internal links
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener("click", function (e) {
        e.preventDefault();

        document.querySelector(this.getAttribute("href"))
            ?.scrollIntoView({
                behavior: "smooth"
            });
    });
});

// Print a welcome message in the browser console
console.log("Welcome to Infinity Academy ✨");
