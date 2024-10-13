const pixel_container = document.getElementById("pixel_container");
const color_palette = document.getElementById("color_palette");
const send_button = document.getElementById("send_button"); 

color_picker

const color_selector_label = document.getElementById("color_picker_label"); 
const color_selector = document.getElementById("color_picker"); 

const popup_container = document.getElementById("popup_container"); 
const popup_message = document.getElementById("popup_message"); 

// Tools : 
const t_bucket = document.getElementById("t_bucket"); 
const t_clear = document.getElementById("t_clear"); 
const t_brush = document.getElementById("t_brush"); 
const t_picker = document.getElementById("t_picker"); 


const COLOR_COUNT = 8 * 3; 


var pixel_matrix = []; 
var preset_color = ["#000000", "#ffa8d9", "#ffc300", "#c70039", "#00a896", "#9b59b6", "#1f618d", "#e74c3c"];

var tool_type = 0; 
var tool_color = "#000000";


function init_pixel_matrix(pixel_matrix, width, height) {
    /*
    Initialise every pixel of the matrix grid to white. 
    */
    for (var pixel_id = 0; pixel_id < width * height; pixel_id++) {
        // Initialise the list of pixel. 
        pixel_matrix[pixel_id] = tool_color; 
        
        // Create the html pixel element. 
        const pixel = document.createElement("div");
        pixel.id = "p_" + pixel_id;
        pixel.classList.add("pixel");
        pixel.style.backgroundColor = pixel_matrix[pixel_id]; 

        // Add border radius to all four corners. 
        switch (pixel_id) {
            case 0:
                pixel.style.borderRadius = "10px 0 0 0";
                break; 
            case 7:
                pixel.style.borderRadius = "0 10px 0 0";
                break; 
            case 56:
                pixel.style.borderRadius = "0 0 0 10px";
                break; 
            case 63:
                pixel.style.borderRadius = "0 0 10px 0";
                break; 
        }

        // Add a click event listener. 
        pixel.addEventListener("click", function() {
            pixel_id = this.id.slice(2); 

            switch(tool_type) {
                case 0: 
                    change_pixel_color(pixel_id);
                    break; 
                
                case 1:
                    fill_area(pixel_id, pixel_matrix); 
                    break;
            }
            
        });
        
        // Add the element to the page. 
        pixel_container.appendChild(pixel); 
    }
}


function change_pixel_color(pixel_id) {
    /*
    Function that change the color of a pixel. 
    */

   // Change the pixel color in the list. 
    pixel_matrix[pixel_id] = tool_color; 

    // Update the color of the pixel. 
    const pixel = document.getElementById("p_" + pixel_id); 
    pixel.style.backgroundColor = pixel_matrix[pixel_id]; 
}


function init_tools_color(preset_color) {
    /*
    Initialise presets colors and color slots. 
    */

    for (var color_id = 0; color_id < COLOR_COUNT; color_id++) { 
        
        // Add white color to complete the color selector. 
        if (!preset_color[color_id]) {
            preset_color[color_id] = "#ffffff"; 
        }

        const color = document.createElement("div");
        color.id = "tc_" + color_id;
        color.classList.add("color");
        color.style.backgroundColor = preset_color[color_id]; 

        // Add a click event listener. 
        color.addEventListener("click", function() {
            color_id = this.id.slice(3); 
            change_tool_color(color_id); 
        });
        
        // Add the element to the page. 
        color_palette.appendChild(color); 
    }

    tool_color = preset_color[0]; 
}


function change_tool_color(color_id) {
    /*
    Function that change the tool color. 
    */
    tool_color = preset_color[color_id]; 
}


function convert_hex_to_int_color(hex_color) {
    /*
    Convert an hex color to an interger. 
    */
    return (Number("0x" + hex_color.slice(1))); 
}


function convert_pixel_matrix(pixel_matrix) {
    /*
    Function that convert a hex color to an integer. 
    */
    converted_pixel_map = []; 

    // Convert each pixel value to an integer. 
    pixel_matrix.forEach(pixel_value => {
        converted_pixel_map.push(convert_hex_to_int_color(pixel_value)); 
    });

    // Return the converted list. 
    return converted_pixel_map; 
}


send_button.addEventListener("click", () => {
    var json_data = JSON.stringify({
        "timestamp": Math.floor(Date.now() / 1000), 
        "width": 8,
        "height": 8,
        "pixel_map": convert_pixel_matrix(pixel_matrix),
    });

    let http = new XMLHttpRequest();
    http.open("POST", "img/57001edf/0", true);
    http.setRequestHeader("Content-Type", "application/json");
    http.send(json_data);

    show_popup(true); 
    setTimeout(hide_popup, 1500);
});



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



////////////////////////////////////////////////////////////////////////////////
//                              TOOLS FUNCTIONS                               //
////////////////////////////////////////////////////////////////////////////////


function update_tool_colors() {
    preset_color.pop(); 
    preset_color.unshift(color_selector.value); 
    tool_color = color_selector.value; 

    for (var color_id = 0; color_id < COLOR_COUNT; color_id++) { 
        
        // Add white color to complete the color selector. 
        if (!preset_color[color_id]) {
            preset_color[color_id] = "#ffffff"; 
        }

        const color = document.getElementById("tc_" + color_id);
        color.style.backgroundColor = preset_color[color_id]; 
    }
}

function clear_pixel_matrix(pixel_matrix) {
    for (var id = 0; id < pixel_matrix.length; id++) {
        pixel_matrix[id] = "#000000"; 
        const pixel = document.getElementById("p_" + id);
        pixel.style.backgroundColor = pixel_matrix[id]; 

    }
}


function fill_area(pixel_id, pixel_matrix, color_to_replace = -1) {
    /*
    Function that fill every pixel with the same color at once. 
    */

    pixel_id = parseInt(pixel_id); 

    // If the pixel id that need to be painted is out of bound, stop. 
    if (pixel_id < 0 || pixel_id > 63) {
        return; 
    }

    // If the pixel is already painted in the correct color, stop. 
    if (pixel_matrix[pixel_id] == tool_color) {
        return; 
    }

    // If the color to replace is not defined, defines it. 
    if (color_to_replace == -1) {
        color_to_replace = pixel_matrix[pixel_id]; 
    } 

    // If the pixel color correspond to the color that need to replace, replace it. 
    if (pixel_matrix[pixel_id] != color_to_replace) {
        return
    }

    // Update color of the pixel. 
    pixel_matrix[pixel_id] = tool_color; 
    const pixel = document.getElementById("p_" + pixel_id); 
    pixel.style.backgroundColor = tool_color; 

    // Check if all four pixels are in bound and paint it. 
    if ((pixel_id + 1) % 8 != 0) {
        fill_area(pixel_id + 1, pixel_matrix, color_to_replace); 
    }

    if ((pixel_id - 1) % 8 != 7) {
        fill_area(pixel_id - 1, pixel_matrix, color_to_replace); 
    }

    if (pixel_id + 8 <= 63) {
        fill_area(pixel_id + 8, pixel_matrix, color_to_replace); 
    }

    if (pixel_id - 8 >= 0) {
        fill_area(pixel_id - 8, pixel_matrix, color_to_replace); 
    }
}


t_brush.addEventListener("click", () => {
    // Change the tool type to brush. 
    tool_type = 0; 
});

t_bucket.addEventListener("click", () => {
    // Change the tool type to bucket. 
    tool_type = 1; 
});

t_clear.addEventListener("click", () => {
    // Clear the matrix screen. 
    clear_pixel_matrix(pixel_matrix); 
});


t_picker.addEventListener("click", () => {
    color_selector_label.click(); 
});

init_pixel_matrix(pixel_matrix, 8, 8);
init_tools_color(preset_color);