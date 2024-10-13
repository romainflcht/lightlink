#include "eeprom_reading.h"


Preferences preferences;

char device_id[DEVICE_ID_BUFFER_SIZE]; 
char wifi_ssid[WIFI_SSID_BUFFER_SIZE]; 
char wifi_pass[WIFI_PASS_BUFFER_SIZE]; 

String ssid; 
String password; 
String identifier; 

void init_preferences() {
  preferences.begin(NAMESPACE, false);

  *ssid = preferences.getString("wifi_ssid", ""); 
  *password = preferences.getString("wifi_pass", "");
  *identifier = preferences.getString("device_id", ""); 

  if (*ssid == "" || *password == "" || *identifier == "") {
    _DEBUG_PRINTLN_("- [DEBUG] No SSID or password set, going to flash mode.");
    tft_draw_popup("CREDENTIALS", "No credentials set", "waiting flash...");

    for (;;) {
      if (Serial.available()) {
        read_serial(); 
      }
    }
  }
}


void read_serial() {
    char      c; 
    uint8_t   parsing_stage; 
    uint8_t   index; 

    parsing_stage = 0; 
    index = 0; 

    while (Serial.available()) {

      // Fetch the next char from the serial. 
      c = Serial.read();

      // Check if the char is a delimiter. 
      if (c == ';') {

        // Check if the parsing stage is the last one. 
        if (parsing_stage >= 2) {
          break; 
        }

        // Reset the index and move to the next parsing stage.
        parsing_stage++; 
        index = 0; 
        continue; 
      } 

      // Save the char in the correct variable according to the parsing stage. 
      if (parsing_stage == 0) {
        device_id[index] = c; 
        check_buffer_overflow(index, DEVICE_ID_BUFFER_SIZE); 
      }
      
      else if (parsing_stage == 1) {
        wifi_ssid[index] = c; 
        check_buffer_overflow(index, WIFI_SSID_BUFFER_SIZE); 
      }

      else if (parsing_stage == 2) {
        wifi_pass[index] = c; 
        check_buffer_overflow(index, WIFI_PASS_BUFFER_SIZE); 
      }

      index++;
    }

    tft_draw_popup("CREDENTIALS", "Credentials set!", "rebooting...");
    delay(5000); 
    ESP.restart(); 
}


void check_buffer_overflow(uint8_t current_index, uint8_t max_buffer_size) {
  if (current_index + 1 >= max_buffer_size) {

    uint8_t counter; 
    for (counter = 10; counter > 0; counter--) {
      tft_draw_popup("CREDENTIALS", "Error, rebooting", "in " + counter + " sec."); 
      delay(1000); 
    }

    ESP.restart(); 
  }

  return; 
}
