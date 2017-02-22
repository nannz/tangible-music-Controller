#include <Wire.h>
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
uint8_t driveEffect = 13; //the effect of the vibrating motor.
int motorLevel = 0;
int potenDriveEffect = 80;
int fsrClickDriveEffect = 30; //real time level of the motor.
int fsrPressDriveEffect = 80;

//the fsr sensor and states
int fsrPin = A1;
int fsrReading;
int curFsrState = LOW;
int prevFsrState = LOW;
long fsrDownTime = -1;
long fsrUpTime = -1;
int fsrHoldTime = 100; // ms hold period: how long to wait for press+hold event
int fsrLongHoldTime = 1000; // ms long hold period: how long to wait for press+hold event

//latching button for speed
const int latchingButPin = 7; //the number pin of the latching button
int latchingButState = LOW; // variable for reading the latching push button
int prevLatchingButState = LOW;
int readingLatchingButState = LOW;
long debounce2 = 20;

//soft rotary potentiometer
int softpotPin = A0; //Analog pin A0
int curPotenVal = 512; //value from the potenmeter
int prevPotenVal = 512;
bool potenState = false;

int responseDelay = 70;
//state of the rotary potentiometer.
int notTouchPoint = 1000;
int curPotenState = 0; //0 is stop, 1 is left, 2 is right
int prevPotenState = 3;

//the micro switch.
int microSwitchInPin = 2;         // the number of the input pin
int microSwitchState = LOW;      // the current state of the output pin
int readingMicroSwitch;           // the current reading from the input pin
int previousMicroSwitch = LOW;    // the previous reading from the input pin
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 20;   // the debounce time, increase if the output flickers

void setup() {
  Serial.begin(9600);
  digitalWrite(softpotPin, HIGH); //enable pullup resistor
  pinMode(microSwitchInPin, INPUT); // set the input pin of the microswitch.
  pinMode(latchingButPin, INPUT);
  //begin the motor drive
  drv.begin();
  drv.setMode(DRV2605_MODE_REALTIME);
}

void loop() {
  curPotenVal = analogRead(softpotPin);
  if(curPotenVal >=360 && curPotenVal <= 375){
    curPotenVal = 0;
  }
  //Serial.println(curPotenVal);
  //reading the latching button switch state for speed of the song.
  readingLatchingButState = digitalRead(latchingButPin);
  //reading the micro switch state for random song.
  readingMicroSwitch = digitalRead(microSwitchInPin);
  //reading the fsr value
  fsrReading = analogRead(fsrPin);
  //Serial.println(fsrReading);
  if (fsrReading <= 500) {
    curFsrState = LOW;
  } else {
    curFsrState = HIGH;
  }
  //-----------------------------------------------------//

  if (curFsrState == HIGH && prevFsrState == LOW) {
    //press down
    fsrDownTime = millis();
//    Serial.print("fsrDownTime: ");
//    Serial.println(fsrDownTime);
  }
  if (curFsrState == LOW && prevFsrState == HIGH) {
    //press up
    fsrUpTime = millis();
//    Serial.print("fsrUpTime: ");
//    Serial.println(fsrUpTime);
  }
  //remind the click time is enough.
  if (curFsrState == HIGH && (millis() - fsrDownTime) >= fsrHoldTime) {
    Serial.println("It's enough hold time.");
    motorLevel = fsrClickDriveEffect;
    //remind the press time is enough.
    if ((millis() - fsrDownTime) >= fsrLongHoldTime) {
      Serial.println("It's enough press time.");
      motorLevel = fsrPressDriveEffect;
    }
  }
  //trigger the function
  if (curFsrState == LOW && prevFsrState == HIGH ) {
    if ((fsrUpTime - fsrDownTime) >= fsrHoldTime) {
      if ((fsrUpTime - fsrDownTime) >= fsrLongHoldTime) {
        Serial.println("trigger long pressed");
        motorLevel = 0;
      } else {
        Serial.println("trigger clicked");
        motorLevel = 0;
      }
    } else {
      motorLevel = 0;
    }
  }
  prevFsrState = curFsrState;

  //-----------------------------------------------------//

  //the latching button to control the speed of a song.
  prevLatchingButState = speedControl(readingLatchingButState, prevLatchingButState, debounce2);
  
  //-----------------------------------------------------//

  //the micro switch to play a random song.
  if (readingMicroSwitch != previousMicroSwitch && millis() - time > debounce) {
    if (microSwitchState == HIGH) {
      microSwitchState = LOW;
      //Serial.println(switchState);
    } else {
      microSwitchState = HIGH;
      Serial.println("random song");
    }
    time = millis();
  }
  previousMicroSwitch = readingMicroSwitch;

  //-----------------------------------------------------//

  //the rotary potentiometer. determining states.
  if (curPotenVal < notTouchPoint && curPotenVal >10) {
    //Serial.println(curPotenVal);
    if (curPotenVal - prevPotenVal < -20) { //to decrease the noise
      //turn left
      curPotenState = 1;
      motorLevel = potenDriveEffect;
    } else if (curPotenVal - prevPotenVal > 20) {
      //turn right
      curPotenState = 2;
      motorLevel = potenDriveEffect;
    } else {
      //not move
      curPotenState = 0;
      motorLevel = 0;
    }
    if (curPotenState == 0 && prevPotenState == 1) { //play previous sone
      Serial.println("skip back");
      motorLevel = 0;
    }
    if (curPotenState == 0 && prevPotenState == 2) {
      Serial.println("skip ahead");
      motorLevel = 0;
    }
    //if now is stop and prev is left -> 前一首
    //if now is stop and prev is right -> 后一首
    prevPotenState = curPotenState;
    prevPotenVal = curPotenVal;
  }

  //run the motor.
  drv.setRealtimeValue(motorLevel);
  delay(responseDelay);
}

int speedControl(int readingLatchingButState, int prevLatchingButState,
                 long debounce2) {
  //the latching button to control the speed of a song.
  if (readingLatchingButState != prevLatchingButState && millis() - time > debounce2) {
    if (readingLatchingButState == HIGH) {
      Serial.println("original speed");
    } else {
      Serial.println("2X speed");
    }
    time = millis();
  }
  prevLatchingButState = readingLatchingButState;
  return prevLatchingButState;
}


