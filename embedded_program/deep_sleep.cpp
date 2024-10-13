#include "deep_sleep.h"


ESP32Time rtc(3600);
uint64_t sleep_start_timer;
RTC_DATA_ATTR uint8_t first_boot = 1;
RTC_DATA_ATTR uint32_t last_timestamp = 0; 
esp_sleep_wakeup_cause_t wakeup_reason;


void deep_sleep_init() {
  /*
  Initialise the deep sleep timer and external wakeup of the esp32. 
  */
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 0);
  esp_sleep_enable_timer_wakeup(SLEEP_DURATION * MICRO_SEC_TO_SEC_FACTOR);

  return; 
}


void rtc_init() {
  /*
  Initialise the RTC for the sleep timer. 
  */
  sleep_start_timer = rtc.getEpoch();

  // If it is the first boot, set the first boot to.
  if (first_boot) {
    first_boot = 0; 
  }

  return; 
}


void check_wakeup_reason() {
  /*
  Check if the wakeup is caused by the timer. In this case check the server timestamp and go to sleep 
  if the timestamp is the same or older. 
  */
  wakeup_reason = esp_sleep_get_wakeup_cause();

  if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER) {
    _DEBUG_PRINTLN_("- [DEEP_SLEEP] Woke up by timer, checking the server timestamp...")

    // If the esp wokeup from timer and server timestamp didn't change go back to sleep. 
    if (!check_server_timestamp(last_timestamp)) {
      _DEBUG_PRINTLN_("- [DEEP_SLEEP] No new drawing detected, go to sleep.")
      esp_deep_sleep_start();
    }
  }

  _DEBUG_PRINTLN_("- [DEEP_SLEEP] Boot or woke up by external input...")

  // Haptic feedback of the wakeup. 
  haptic(); 

  // init the screen matrix and undim the matrix screen. 
  init_matrix();
  undim_screen();
  return; 
}

uint32_t get_last_timestamp() {
  /*
  Getter that return the last fetched timestamp. 
  */
  return last_timestamp; 
}

uint8_t is_first_boot() {
  /*
  Getter that return the boot count. 
  */
  return first_boot; 
}


void update_last_timestamp(uint32_t new_timestamp) {
  /*
  Setter that set the last fetched timestamp value. 
  */
  last_timestamp = new_timestamp; 
  return; 
}


void reset_sleep_timer() {
  sleep_start_timer = rtc.getEpoch(); 
}


void go_to_sleep_on_timer(uint8_t force_sleep) {
  /*
  Function that set the esp to sleep after a timer. 
  */

  if (force_sleep) {
    _DEBUG_PRINTLN_("- [DEEP_SLEEP] Going to sleep on timer. Zzzzzzz.")
    dim_screen(); 
    esp_deep_sleep_start(); 
  }

  _DEBUG_PRINT_("- [DEBUG] Timer state : ")
  _DEBUG_PRINTLN_(rtc.getEpoch() - sleep_start_timer)

  // Check if the timer is expire, if so dim the matrix screen and go to sleep. 
  if (rtc.getEpoch() - sleep_start_timer >= GO_TO_SLEEP_TIMER_DURATION) {
    _DEBUG_PRINTLN_("- [DEEP_SLEEP] Going to sleep on timer. Zzzzzzz.")
    dim_screen(); 
    esp_deep_sleep_start(); 
  }
}
