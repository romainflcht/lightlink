#include "vibration_motor.h"


void vibrate() {
  /*
  Vibrate the motor.
  */
  digitalWrite(VIBRATION_MOTOR_PIN, 1); 
  delay(200); 
  digitalWrite(VIBRATION_MOTOR_PIN, 0); 
  delay(100); 
  digitalWrite(VIBRATION_MOTOR_PIN, 1); 
  delay(200); 
  digitalWrite(VIBRATION_MOTOR_PIN, 0); 
  return; 
}


void haptic() {
  digitalWrite(VIBRATION_MOTOR_PIN, 1); 
  delay(60); 
  digitalWrite(VIBRATION_MOTOR_PIN, 0); 
}