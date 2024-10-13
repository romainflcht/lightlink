#include "tft_screen.h"

TFT_eSPI tft = TFT_eSPI();


void init_tft() {
  /*
  Function that initialise the tft screen and clear it. 
  */
  tft.init();
  tft.setRotation(TFT_PORTRAIT);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
}

void tft_draw_status_bar(int16_t wifi_status) {
  /*
  Function that draw the status bar according to the wifi status.
  :param: wifi_status: The current wifi status of the wifi module. 
  */

  // Draw the text and the line that separate the status bar from the UI.
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Lightlink", 2, 2, 2);
  tft.drawLine(0, 20, TFT_SCREEN_WIDTH, 20, TFT_WHITE);

  // Draw the battery indicator.
  tft_draw_symetric_bitmap(TFT_SCREEN_WIDTH - 2 - (DEFAULT_ICON_SIZE * 2), 2, BATTERY_ICON, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE, TFT_WHITE, TFT_BLACK);
  tft_draw_battery_indicator(TFT_SCREEN_WIDTH - 2 - (DEFAULT_ICON_SIZE * 2), 2, get_battery_level());

  // Draw the battery charge symbol. 
  if (is_battery_charging()) {
    tft.drawXBitmap(TFT_SCREEN_WIDTH - 2 - (DEFAULT_ICON_SIZE * 2), 2, BATTERY_CHARGE_ICON, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE, 0, TFT_WARNING);
  }

  // Draw the wifi icon and its state according to his status.
  tft_draw_symetric_bitmap(TFT_SCREEN_WIDTH - 2 - DEFAULT_ICON_SIZE, 2, WIFI_ICON, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE, TFT_WHITE, TFT_BLACK);

  switch (wifi_status) {
    case 0:
      break;

    case 1:
      tft_draw_symetric_bitmap(TFT_SCREEN_WIDTH - 2 - DEFAULT_ICON_SIZE, 2, ERROR_ICON, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE, TFT_ERROR, TFT_NO_BG);
      break;

    default:
      tft_draw_symetric_bitmap(TFT_SCREEN_WIDTH - 2 - DEFAULT_ICON_SIZE, 2, WARNING_ICON, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE, TFT_WARNING, TFT_NO_BG);
      break;
  }
}


void tft_draw_popup(String title, String message1, String message2) {
  /*
  Function that draw a message box. 
  :param: title: The title of the message box. 
  :param: message: the content of the message box. 
  */
  tft.fillRect(7, 35, TFT_SCREEN_WIDTH - 14, 50, TFT_BLACK);
  tft.drawRect(7, 35, TFT_SCREEN_WIDTH - 14, 50, TFT_WHITE);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(title, 13, 25, 2);
  tft.drawCentreString(message1, TFT_SCREEN_WIDTH / 2, 40, 2);
  tft.drawCentreString(message2, TFT_SCREEN_WIDTH / 2, 56, 2);
}


void tft_draw_symetric_bitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, int32_t bgcolor) {
  /*
  Function that take only the left part of a symetric bitmap and draw the full 
  bitmap by flipping it vertically. Used to save memory space.
  :param: x: vertical position on screen where the bitmap will be draw. 
  :param: y: horizontal position on screen where the bitmap will be draw. 
  :param: w: width of the entire icon, not of the symetric part. 
  :param: h: height of the icon. 
  :param: bitmap: the bitmap that need to be displayed. 
  */

  for (uint8_t flipped = 0; flipped < 2; flipped++) {
    // If we don't want background color, use this function to draw the bitmap.
    if (bgcolor == TFT_NO_BG) {
      tft.drawXBitmap(x + (8 * flipped) - flipped, y, bitmap, w / 2, h, flipped, color);
      continue;
    }

    // Else use this one to draw the background.
    tft.drawXBitmap(x + (8 * flipped) - flipped, y, bitmap, w / 2, h, flipped, color, bgcolor);
  }
}


void tft_draw_battery_indicator(uint16_t x, uint16_t y, uint8_t battery_level) {
  /*
  Function that draw the battery level indicator.
  :param: battery_level: value between 0 and 100. 
  */
  uint16_t color;

  // Check the battery level range.
  if (66 <= battery_level && battery_level <= 100) {
    // Battery level between 100% and ~66%.
    color = TFT_VALID;
  }

  else if (33 <= battery_level && battery_level <= 66) {
    // Battery level between ~66% and ~33%, change the indicator height and color.
    color = TFT_WARNING;
    y += 3;
  }

  else {
    // Battery level between ~33% and below, change the indicator height and color.
    color = TFT_ERROR;
    y += 6;
  }

  // Draw the indicator.
  tft.fillRect(x + 6, y + 5, 4, 8 - (y - 2), color);
  return;
}


void tft_draw_text(String text, uint16_t x, uint16_t y) {
  tft.setCursor(x, y);
  tft.print(text);

  return; 
}

void tft_clear() {
  tft.fillScreen(TFT_BLACK); 
}


void tft_draw_qr_code() {
  /*

  */
  int32_t byte_width = (QRCODE_ICON_SIZE + 7) / 8;

  for (int32_t y = 0; y < QRCODE_ICON_SIZE; y++) {
    for (int32_t x = 0; x < QRCODE_ICON_SIZE; x++) {
      if (pgm_read_byte(QRCODE + y * byte_width + x / 8) & (128 >> (x & 7))) {

        tft.fillRect(5 + x * 5, TFT_SCREEN_HEIGHT - 130 + y * 5, QRCODE_PIXEL_SIZE, QRCODE_PIXEL_SIZE, TFT_WHITE); 
        continue; 
      }

      tft.fillRect(5 + x * 5, TFT_SCREEN_HEIGHT - 130 + y * 5, QRCODE_PIXEL_SIZE, QRCODE_PIXEL_SIZE, TFT_BLACK); 
    }
  }
}
