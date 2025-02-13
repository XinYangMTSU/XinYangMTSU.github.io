function changeColor() {

    let selectedColor = document.getElementById("colorSelect").value;
    let body = document.body;
    let message = document.getElementById("message");

    switch (selectedColor) {
        case "red":
            body.style.backgroundColor = "red";
            message.innerText = "You picked Red! \u{1F534}";
            break;
        case "blue":
            body.style.backgroundColor = "blue";   
            message.innerText = "You picked Blue! \u{1F535}";
            break;
        case "green":
            body.style.backgroundColor = "green";
            message.innerText = "You picked Green! \u{1F7E2}";
            break;
        case "yellow":
            body.style.backgroundColor = "yellow";
            message.innerText = "You picked Yellow! \u{1F7E1}";
            break;
        case "purple":
            body.style.backgroundColor = "purple";
            message.innerText = "You picked Purple! \u{1F7E3}";
            break;
        case "white":
            body.style.backgroundColor = "white";
            message.innerText = "You picked White! \u26AA";
            break;
        default:
            message.innerText = "Please select a color!";
            break;
    }
}
