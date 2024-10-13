#include "wifi.h"

uint8_t wifi_status = 1;


void init_wifi() {
  /*
  Function that initialise the wifi connection and wait to connect to a hotspot. 
  */

  String ssid; 
  String password; 

  WiFi.setHostname(DEVICE_NAME);
  WiFi.begin(ssid, password);

  _DEBUG_PRINT_("- [WiFi] Waiting to connect to wifi hotspot")

  // Wait to connect to the wifi.
  String dots = "";
  int timeout_timer = millis(); 
  while (WiFi.status() != WL_CONNECTED) {
    // Draw popup with dot animation. 
    tft_draw_status_bar(wifi_status); 
    tft_draw_popup("WiFi", "CONNECTING" + dots);
    _DEBUG_PRINT_(".")

    dots += ".";
    if (dots.length() > 3) { dots = ""; }
    delay(300);

    if (millis() - timeout_timer >= HOTSPOT_CONNECTION_TIMEOUT) {
      break; 
    }
  }

  _DEBUG_PRINTLN_("\n- [WiFi] Connected ! ")
  wifi_status = 0; 
  return; 
}


int check_wifi_connection() {
  /*
  Function check the wifi conection status.
  :return: 0 if the device is connected to internet and 1 otherwise.
  */

  if (WiFi.status() == WL_CONNECTED) {
    // Update wifi status.
    wifi_status = 0; 
    return 0;
  }

  // Update wifi status.
  wifi_status = 1; 
  return 1;
}


int fetch_url(String *recieved_data_buffer, String url) {
  // Check if the client is connected to the internet. 
  if (check_wifi_connection()) {
    return 1;
  }

  // Initialise the HTTP client and start the get request to the url.
  HTTPClient http;
  http.begin(url);
  int16_t http_status = http.GET();

  switch (http_status) {
    // The request was successful, retrieve url content.
    case HTTP_CODE_OK:
      *recieved_data_buffer = http.getString();
      break;

    // url doesn't exist.
    case HTTP_CODE_NOT_FOUND:
      _DEBUG_PRINTLN_("- [ERROR] HTTP CODE 404: No drawing linked to this account ?")
      break;

    // Something went wrong during request.
    default:
      http.end();
      wifi_status = 2;
      return 1;
  }

  // End the http client to free memory.
  http.end();
  return 0;
}


int check_server_timestamp(uint32_t last_timestamp) {
  /*
  Function that check the last recieved timestamp and update the display if the timestamp is newer that the last. 
  :param: last_timestamp: last timestamp saved in the RTC memory. 
  :return: 1 if the screen need to be updated, 0 if not. 
  */

  if (last_timestamp <= 0) {
    _DEBUG_PRINTLN_("[DEBUG] Timestamp wasn't initialised, initializing...")
    return 1;
  }

  // Allocate the timestamp buffer that will contain the result of the request. 
  String req_server_ts_buffer; 
  if (fetch_url(&req_server_ts_buffer, SERVER_URL DEVICE_ID "/1")) {
    // Error during the request to the server, don't update the matrix screen.
    _DEBUG_PRINTLN_("- [ERROR] Error when fetching last timestamp from server")
    return 0; 
  }

  // Allocate the json timestamp buffer that will contain json data fetched from the server. 
  JsonDocument json_server_ts_buffer;
  DeserializationError error = deserializeJson(json_server_ts_buffer, req_server_ts_buffer.c_str());

  if (error) {
    // An error occured during json parsing, abort. 
    _DEBUG_PRINTLN_("- [ERROR] Error during JSON conversion of the server timestamp")
    return 1;
  }

  uint32_t server_timestamp = json_server_ts_buffer["timestamp"];

  if (server_timestamp > last_timestamp) {
    // The server timestamp is newer that the device last timestamp, update the screen. 
    vibrate();
    return 1; 
  }

  // The server timestamp is older that the device last timestamp, abort. 
  return 0; 
}


int update_drawing() {
  /*
  Fetch the last drawing uploader to the server and displays it on the matrix screen. 
  */

  String req_drawing_obj_buffer; 
  if (fetch_url(&req_drawing_obj_buffer, SERVER_URL DEVICE_ID "/0")) {
    // Error during the request to the server. 
    _DEBUG_PRINTLN_("- [ERROR] Error when fetching last timestamp from server")
    return 1; 
  }

  // Allocate the json drawing buffer that will contain json data fetched from the server. 
  JsonDocument json_drawing_obj_buffer;
  DeserializationError error = deserializeJson(json_drawing_obj_buffer, req_drawing_obj_buffer.c_str());

  if (error) {
    // An error occured during json parsing, abort. 
    _DEBUG_PRINTLN_("- [ERROR] Error during JSON conversion of the drawing.")
    return 1;
  }

  // Convert json data to C type data. 
  uint32_t server_timestamp = json_drawing_obj_buffer["timestamp"];
  uint8_t width = json_drawing_obj_buffer["width"];
  uint8_t height = json_drawing_obj_buffer["height"];
  JsonArray img = json_drawing_obj_buffer["pixel_map"];

  update_last_timestamp(server_timestamp); 
  update_matrix(img, width * height); 
  reset_sleep_timer(); 
  return 0; 
}


uint8_t get_wifi_status() {
  /*
  Getter that return the wifi_status.
  */
  return wifi_status; 
}