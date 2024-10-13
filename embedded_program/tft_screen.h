#ifndef TFT_SCREEN_H
#define TFT_SCREEN_H

#include <SPI.h>
#include <TFT_eSPI.h>
#include "tft_bitmap.h"
#include "battery_management.h"
#include "configuration.h"

// CONSTANTS : 
#define TFT_SCREEN_WIDTH    135
#define TFT_SCREEN_HEIGHT   240

#define TFT_LANDSCAPE     1
#define TFT_PORTRAIT      2
#define TFT_Y_CURSOR_STEP 16

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_NO_BG -1

#define TFT_ERROR   0xF800
#define TFT_WARNING 0xFCE0
#define TFT_VALID   0x2DC5

// FUNCTIONS : 
void init_tft(); 
void tft_draw_status_bar(int16_t wifi_status); 
void tft_draw_popup(String title, String message1, String message2 = ""); 
void tft_draw_symetric_bitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, int32_t bgcolor); 
void tft_draw_battery_indicator(uint16_t x, uint16_t y, uint8_t battery_level); 
void tft_draw_text(String text, uint16_t x, uint16_t y); 
void tft_clear(); 
void tft_draw_qr_code(); 

#endif