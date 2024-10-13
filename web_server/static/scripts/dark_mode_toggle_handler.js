const dark_m_on = document.getElementById("dark_m_on"); 
const dark_m_off = document.getElementById("dark_m_off"); 


var is_dark_mode_on = false; 


dark_m_on.addEventListener("click", () => {
    // Dark mode is on and need to be turned off. 
    dark_m_on.classList.remove("dark_m_active"); 
    dark_m_off.classList.add("dark_m_active"); 

    is_dark_mode_on = false; 
});


dark_m_off.addEventListener("click", () => {
    // Dark mode is off and need to be turned on. 
    dark_m_on.classList.add("dark_m_active"); 
    dark_m_off.classList.remove("dark_m_active"); 

    is_dark_mode_on = true; 
});