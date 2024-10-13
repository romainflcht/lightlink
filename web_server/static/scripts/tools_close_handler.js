const menu_item = document.getElementById("menu_item");
const tool_container = document.getElementById("tool_container");

var menu_is_open = false; 


menu_item.addEventListener("click", () => {
    if (menu_is_open) {
        // Close the menu.
        menu_item.style.transform = "rotate(180deg)"; 
        tool_container.style.bottom = "-160px"; 
        
    }

    else {
        // Open the menu. 
        menu_item.style.transform = "rotate(0deg)"; 
        tool_container.style.bottom = "0"; 
    }

    menu_is_open = !menu_is_open; 
    return; 
})