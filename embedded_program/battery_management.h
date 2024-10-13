#ifndef BATTERY_MANAGEMENT_H
#define BATTERY_MANAGEMENT_H

#include "Pangodream_18650_CL.h"
#include "tft_screen.h"
#include "configuration.h"

// CONSTANTS : 
#define BATTERY_INDICATOR_PIN  34
#define CONVERSION_FACTOR     1.8
#define MIN_USB_VOLTAGE       4.8
#define MAX_BATTERY_VOLTAGE   4.2
#define MIN_BATTERY_VOLTAGE   3.2

// FUNCTIONS :
uint8_t get_battery_level(); 
uint8_t is_battery_charging();  

#endif