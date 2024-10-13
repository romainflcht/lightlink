#ifndef MATRIX_SCREEN_H
#define MATRIX_SCREEN_H

#include <FastLED.h>
#include <ESP32Time.h>
#include <ArduinoJson.h>
#include "configuration.h"

// CONSTANTS : 
#define SCREEN_WIDTH             8
#define SCREEN_HEIGHT            8
#define SCREEN_PIXEL_COUNT      64
#define SCREEN_DATA_PIN         13
#define SCREEN_BRIGHTNESS       25
#define SCREEN_SLEEP_BRIGHTNESS  0

#define RED               0xFF0000
#define GREEN             0x00FF00
#define BLUE              0x0000FF

// FUNCTIONS : 
void init_matrix();
void update_matrix(JsonArray drawing, uint8_t drawing_length); 
void dim_screen();
void undim_screen();

#endif