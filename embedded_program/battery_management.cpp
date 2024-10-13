#include "battery_management.h"

Pangodream_18650_CL BL(BATTERY_INDICATOR_PIN, CONVERSION_FACTOR, 20);


uint8_t get_battery_level() {
  /*
  Return the calculated battery level. 
  */
  return BL.getBatteryChargeLevel(); 
}


uint8_t is_battery_charging() {
  /*
  Return 1 if the battery is change, 0 otherwise. 
  */
  return BL.getBatteryVolts() >= MIN_USB_VOLTAGE; 
}
