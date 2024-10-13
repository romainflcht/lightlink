#ifndef EEPROM_READING_H
#define EEPROM_READING_H

#include <Preferences.h>
#include "configuration.h"
#include "tft_screen.h"

// CONSTANTS : 
#define NAMESPACE "lightlink"

#define DEVICE_ID_BUFFER_SIZE  9
#define WIFI_SSID_BUFFER_SIZE  50
#define WIFI_PASS_BUFFER_SIZE  50

// FUNCTIONS : 
void init_preferences(); 
void read_serial(); 
void check_buffer_overflow(uint8_t current_index, uint8_t max_buffer_size); 
#endif