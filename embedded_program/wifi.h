#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h> 
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "configuration.h"
#include "matrix_screen.h"
#include "deep_sleep.h"
#include "tft_screen.h"
#include "eeprom_reading.h"
#include "vibration_motor.h"

// CONSTANTS : 
#define SSID                       "iPhone de Romain"
#define PASSWD                     "Cestlemotdepasse"
#define SERVER_URL                 "http://lightlink.ddns.net/img/"
#define HOTSPOT_CONNECTION_TIMEOUT 5000

// FUNCTIONS : 
void init_wifi(); 
int check_wifi_connection(); 
int fetch_url(String *recieved_data_buffer, String url); 
int check_server_timestamp(uint32_t last_timestamp);
int update_drawing(); 
uint8_t get_wifi_status(); 

#endif