let goTopBtn = document.getElementById("goTopBtn");
function topFunction() {
    document.body.scrollTop = 0;
    document.documentElement.scrollTop = 0;
}
goTopBtn.onclick = topFunction;
