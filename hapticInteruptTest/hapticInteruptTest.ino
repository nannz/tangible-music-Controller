#include <Wire.h>           // the motor drier uses I2C
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 motor;     // instance of the motor driver library
uint8_t effect = 1;
void setup() {
  Serial.begin(9600);       // initialize serial communication
  motor.begin();            // initialize motor driver communication
  // set the motor into realtime mode:
  //motor.setMode(DRV2605_MODE_REALTIME);
  motor.setMode(DRV2605_MODE_INTTRIG); 
}

void loop() {
  int sensor = analogRead(A0);              // read the potentiometer
  int level = map(sensor, 0, 1023, 0, 100); // mapt it to 0 - 100             
//  motor.setRealtimeValue(level);            // set the motor's realtime level
//  Serial.println(level);                    // print the level

  motor.setWaveform(0, effect);  // play effect 
  motor.setWaveform(1, 0);       // end waveform

  // play the effect!
  motor.go();
  delay(500);
}
