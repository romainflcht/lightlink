#include "configuration.h"
#include "wifi.h"
#include "tft_screen.h"
#include "matrix_screen.h"
#include "deep_sleep.h"
#include "battery_management.h"
#include "eeprom_reading.h"
#include "vibration_motor.h"



void setup() {
  _DEBUG_START_(BAUD_RATE)
  _DEBUG_PRINTLN_("\n\n")

  // Initialise wakeup method for the deep sleep. 
  deep_sleep_init(); 

  // Initialise vibration and battery pin. 
  pinMode(BATTERY_INDICATOR_PIN, INPUT);
  pinMode(VIBRATION_MOTOR_PIN, OUTPUT);

  // Show the last drawing saved to the device. 
  FastLED.show(); 

  // If it's the first boot, initialise the screen before wifi to see the connection process. 
  if (is_first_boot()) {
    init_tft(); 
    tft_draw_status_bar(get_wifi_status()); 
    tft_draw_text("v"SOFTWARE_VERSION, 0, TFT_SCREEN_HEIGHT - 7);
    haptic();
  }

  init_preferences(); 

  // Initialise wifi to be able to check the server timestamp. 
  init_wifi();

  // Go back to sleep if the server timestamp is the same as the device last timestamp. 
  check_wakeup_reason(); 

  // Initialise every component of the device.
  if (!is_first_boot()) {
    init_tft(); 
    tft_draw_status_bar(get_wifi_status()); 
    tft_draw_text("v"SOFTWARE_VERSION, 0, TFT_SCREEN_HEIGHT - 7);
  }
  
  rtc_init();
  tft_clear(); 
  tft_draw_popup("Application", "Scan QRCODE"); 
  tft_draw_qr_code(); 
  tft_draw_text("v"SOFTWARE_VERSION, 0, TFT_SCREEN_HEIGHT - 7);
}

void loop() {
  tft_draw_status_bar(get_wifi_status()); 
  
  // Check the server timestamp and update the screen if a newer drawing exist.  
  uint32_t last_timestamp = get_last_timestamp(); 
  if (check_server_timestamp(last_timestamp)) {
    update_drawing(); 
  }

  // Check the rtc timer and go to sleep if the timer expire. 
  go_to_sleep_on_timer(); 
  delay(1000); 
}
