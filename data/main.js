var myButton = document.getElementById("mi_boton");
var myText = document.getElementById("mi_texto");
var count = 0;

myButton.onclick = function() {
    count++;
    myText.innerHTML = count;
}
