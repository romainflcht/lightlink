const imageFolder = '../static/img/pixelart/';
const pixelArtContainer = document.getElementById('pixel_art');
const selectButton = document.getElementById('select_button');
const sendButton = document.getElementById('select_button'); // Assure-toi que l'ID du bouton d'envoi est correct

let selectedImage = null;

const imageFiles = [
    'apple.png',
    'batman.png',
    'battery.png',
    'bell.png',
    'broken_heart.png',
    'cactus.png',
    'chrismas.png',
    'cup.png',
    'flowers.png',
    'ghost.png',
    'glass_bottle.png',
    'heart.png',
    'ice_cream.png',
    'kermit.png',
    'key.png',
    'lightning.png',
    'lolipop.png',
    'luke.png',
    'mushroom.png',
    'poop.png',
    'r2.png',
    'skull.png',
    'spidey.png',
    'tv.png',
    'vader.png',
    'yoda.png',
];

if (pixelArtContainer) {
    imageFiles.forEach(fileName => {
        const img = document.createElement('img');
        img.src = imageFolder + fileName;
        img.alt = fileName.split('.')[0];

        img.addEventListener('click', () => {
            if (selectedImage) {
                selectedImage.classList.remove('selected');
            }
            img.classList.add('selected');
            selectedImage = img;
            selectButton.disabled = false;
            selectButton.classList.add('enabled');
        });

        pixelArtContainer.appendChild(img);
    });

    sendButton.addEventListener("click", () => {
        if (selectedImage) {
            let filename = selectedImage.alt + ".json";
            console.log(filename);
        
            fetch('../static/json/' + filename)
                .then((response) => response.json())
                .then(data => {

                    // Create the JSON payload with the opened json file. 
                    var json_data = JSON.stringify({
                        "timestamp": Math.floor(Date.now() / 1000), 
                        "width": data["width"],
                        "height": data["height"],
                        "pixel_map": data["pixel_map"],
                    });

                    let http = new XMLHttpRequest();
                    http.open("POST", "img/57001edf/0", true);
                    http.setRequestHeader("Content-Type", "application/json");

                    // Send the POST request. 
                    http.send(json_data);

                    // Show the send confirmation popup. 
                    show_popup(true); 
                    setTimeout(hide_popup, 1500); 
                })
                .catch((error) => {
                    console.error("Unable to fetch data:", error); 
                    // Show the error popup. 
                    show_popup(false); 
                    setTimeout(hide_popup, 1500);
                });
        } else {
            console.error("No image selected.");
        }
    });

} else {
    console.error("Element with id 'pixel_art' not found.");
}



function show_popup(is_success) {
    /*
    Show the popup container and the popup message. 
    */
    if (is_success) {
        popup_message.classList.add("success"); 
        popup_message.classList.remove("error"); 
        popup_message.innerHTML = "done"; 
    }

    else {
        popup_message.classList.remove("success"); 
        popup_message.classList.add("error"); 
        popup_message.innerHTML = "error"; 
    }

    popup_container.style.opacity = 1; 
    popup_container.classList.add("show-popup"); 
}


function hide_popup() {
    /*
    Hide the popup container and message. 
    */
    popup_container.style.opacity = 0; 
    setTimeout(() => {
        popup_container.classList.remove("show-popup"); 
    }, 300); 
    
}


popup_message.addEventListener("click", () => {
    hide_popup(); 
}); 
