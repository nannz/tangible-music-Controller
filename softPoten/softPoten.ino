#include <Wire.h>
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;
uint8_t driveEffect = 13; //the effect of the vibrating motor.

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
  drv.selectLibrary(1);
  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);
}

void loop() {
  curPotenVal = analogRead(softpotPin);
  //Serial.println(curPotenVal);
  //reading the latching button switch state for speed of the song.
  readingLatchingButState = digitalRead(latchingButPin);
  //reading the micro switch state for random song.
  readingMicroSwitch = digitalRead(microSwitchInPin);

  //the latching button to control the speed of a song.
  if(readingLatchingButState != prevLatchingButState && millis() - time > debounce2){
    if(readingLatchingButState == HIGH){
      Serial.println("original speed");
    }else{
      Serial.println("2X speed");
    }
    //Serial.println("changeSpeed");
     time = millis();
  }
  prevLatchingButState = readingLatchingButState;

  //the micro switch to play a random song.
  if (readingMicroSwitch == HIGH && previousMicroSwitch == LOW && millis() - time > debounce) {
    if (microSwitchState == HIGH) {
      microSwitchState = LOW;
      //Serial.println(switchState);
    } else {
      microSwitchState = HIGH;
      Serial.println("random song");
    }
    time = millis();
  }

  //the rotary potentiometer. determining states.
  if (curPotenVal < notTouchPoint && curPotenVal != 365 && curPotenVal != 364) {//when not touched, it's automatically 365
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
      runDrive(driveEffect); // play the drive.
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
