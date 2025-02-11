 // 1. Get a reference to the element.
let goTopBtn = document.getElementById("goTopBtn");

// 2. Define the function to scroll to the top.
function topFunction() {
    document.body.scrollTop = 0; // older browsers
    document.documentElement.scrollTop = 0;
}
        
//goTopBtn.onclick = topFunction;

 // 3. Use addEventListener to bind the click event to topFunction.
  goTopBtn.addEventListener('click', topFunction);
