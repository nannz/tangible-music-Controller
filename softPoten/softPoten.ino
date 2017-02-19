#include <Wire.h>
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
uint8_t driveEffect = 13; //the effect of the vibrating motor.
int motorLevel = 0;
int potenDriveEffect = 80;

//latching button for speed
const int latchingButPin = 7; //the number pin of the latching button
int latchingButState = LOW; // variable for reading the latching push button
int prevLatchingButState = LOW;
int readingLatchingButState = LOW;
long debounce2 = 20;

//soft rotary potentiometer
int softpotPin = A0; //Analog pin A0
//int curPotenVal = 512; //value from the potenmeter
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
  //drv.selectLibrary(1);
  //drv.setMode(DRV2605_MODE_INTTRIG);
}

void loop() {
  int curPotenVal = analogRead(softpotPin);
  Serial.println(curPotenVal);
  //reading the latching button switch state for speed of the song.
  readingLatchingButState = digitalRead(latchingButPin);
  //reading the micro switch state for random song.
  readingMicroSwitch = digitalRead(microSwitchInPin);

  //the latching button to control the speed of a song.
  prevLatchingButState = speedControl(readingLatchingButState,prevLatchingButState,debounce2);

//  int microResult[] = {previousMicroSwitch,microSwitchState};
//  microResult = randomSong(readingMicroSwitch,previousMicroSwitch,microSwitchState,debounce);
//  previousMicroSwitch = microResult[0];
//  microSwitchState = microResult[1];
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
  
  //the rotary potentiometer. determining states.
  if (curPotenVal < notTouchPoint && curPotenVal != 365 && curPotenVal != 364 && curPotenVal != 366) {//when not touched, it's automatically 365
    //Serial.println(curPotenVal);
    if (curPotenVal - prevPotenVal < -4) { //to decrease the noise
      //turn left
      curPotenState = 1;
      motorLevel = potenDriveEffect;
    } else if (curPotenVal - prevPotenVal > 4) {
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

  }else{
    motorLevel = 0;
  }
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


