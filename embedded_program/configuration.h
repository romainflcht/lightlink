#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define DEBUG
#define BAUD_RATE               115200

#define SOFTWARE_VERSION       "1.3"
#define DEVICE_NAME            "LightLink v" SOFTWARE_VERSION
#define DEVICE_ID              "57001edf"

// MACROS : 
#ifdef DEBUG
#define _DEBUG_PRINT_(x)    Serial.print(x); 
#define _DEBUG_PRINTLN_(x)  Serial.println(x); 
#define _DEBUG_START_(x)    Serial.begin(x); 
#else
#define _DEBUG_PRINT_(x)
#define _DEBUG_PRINTLN_(x)
#define _DEBUG_START_(x) 
#endif

#endif