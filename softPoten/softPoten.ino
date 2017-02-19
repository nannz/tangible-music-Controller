#include <Wire.h>
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
uint8_t driveEffect = 13;

int softpotPin = A0; //Analog pin A0
int curPotenVal = 512; //value from the potenmeter
int prevPotenVal = 512;
bool potenState = false;

int responseDelay = 50;

int notTouchPoint = 1000;
int curPotenState = 0; //0 is stop, 1 is left, 2 is right
int prevPotenState = 3;

void setup() {
  Serial.begin(9600);
  digitalWrite(softpotPin, HIGH); //enable pullup resistor

  //begin the motor drive
  drv.begin();
  drv.selectLibrary(1);
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 
}

void loop() {
  curPotenVal = analogRead(softpotPin);
  Serial.println(curPotenVal);
  
  if (curPotenVal < notTouchPoint && curPotenVal != 365) {//when not touched, it's automatically 365
    //Serial.println(curPotenVal);
    if (curPotenVal - prevPotenVal < -4) { //to decrease the noise
      //turn left
      curPotenState = 1;
    } else if (curPotenVal - prevPotenVal > 4) {
      //turn right
      curPotenState = 2;
    } else {
      //not move
      curPotenState = 0;
    }
    if (curPotenState == 0 && prevPotenState == 1) { //play previous sone
      Serial.println("skip back");
      runDrive(driveEffect);
    }
    if (curPotenState == 0 && prevPotenState == 2) {
      Serial.println("skip ahead");
      runDrive(driveEffect);
    }
    //if now is stop and prev is left -> 前一首
    //if now is stop and prev is right -> 后一首
    prevPotenState = curPotenState;
    prevPotenVal = curPotenVal;
  }
  delay(responseDelay);
    

}
