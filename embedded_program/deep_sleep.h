#ifndef DEEP_SLEEP_H
#define DEEP_SLEEP_H

#include <ESP32Time.h>
#include "configuration.h"
#include "matrix_screen.h"
#include "vibration_motor.h"
#include "tft_screen.h"
#include "wifi.h"

// CONSTANTS :
#define GO_TO_SLEEP_TIMER_DURATION        30
#define SLEEP_DURATION                     3
#define MICRO_SEC_TO_SEC_FACTOR      1000000

// FUNCTIONS : 
void deep_sleep_init();
void rtc_init(); 
void check_wakeup_reason();
void update_last_timestamp(uint32_t new_timestamp);
uint32_t get_last_timestamp(); 
uint8_t is_first_boot(); 
void reset_sleep_timer(); 
void go_to_sleep_on_timer(uint8_t force_sleep = 0); 

#endif