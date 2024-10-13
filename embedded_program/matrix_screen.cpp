#include "matrix_screen.h"

RTC_DATA_ATTR CRGB matrix_screen[SCREEN_PIXEL_COUNT];



void init_matrix() {
  /*
  Initialise the matrix screen using the fast led library. 
  */

  FastLED.addLeds<WS2812B, SCREEN_DATA_PIN, GRB>(matrix_screen, SCREEN_PIXEL_COUNT);
  FastLED.setBrightness(SCREEN_BRIGHTNESS);
}


void update_matrix(JsonArray drawing, uint8_t drawing_length) {
  /*
  Update the matrix screen with the drawing passed in argument. 
  :param: drawing: array of pixels that will be printed on the screen. 
  :param: drawing_length: size of the drawing array. 
  */

  for (uint8_t cursor; cursor < drawing_length; cursor++) {
    // Convert the pixel color to long.
    uint32_t color = drawing[cursor]; 

    // Update pixel value. 
    matrix_screen[cursor] = color;
  }

  // Update the matrix screen.
  FastLED.show();
  _DEBUG_PRINTLN_("- [INFO] Matrix screen updated!")
}

void dim_screen() {
  /*
  Dim the matrix screen to reduce power consumption in deep sleep mode. 
  */
  FastLED.setBrightness(SCREEN_SLEEP_BRIGHTNESS);

  // Update the screen brightness. 
  FastLED.show();
}

void undim_screen() {
  /*
  Undim the matrix screen on wakeup. 
  */
  FastLED.setBrightness(SCREEN_BRIGHTNESS);

  // Update the screen brightness. 
  FastLED.show();
}