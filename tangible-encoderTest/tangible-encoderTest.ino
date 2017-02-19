/* Encoder Library - Basic Example
   http://www.pjrc.com/teensy/td_libs_Encoder.html

   This example code is in the public domain.
*/

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(5, 6);

//   avoid using pins with LEDs attached

int encButPin = 4;
int encButState = LOW;
int encButPrevState;
int responseDelay = 5; //response delay of the button
long time = 0;         // the last time the output pin was toggled
long debounce = 100;   // the debounce time, increase if the output flickers


void setup() {
  Serial.begin(9600);
  pinMode(encButPin, INPUT);
  digitalWrite(encButPin, LOW);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  //the click button part
  int readingEncButState = digitalRead(encButPin);
  Serial.print("readingEncButState is ");
  Serial.print(readingEncButState);
  Serial.print("; encButPrevState is ");
  Serial.println(encButPrevState);
//  if (readingEncButState == LOW && encButPrevState == HIGH && ( millis() - time > debounce)) {
//    Serial.println("pushing the button ing...");
//    time = millis();
//  } else {
//    
//  }
  //  if (readingEncButState == LOW && encButPrevState == HIGH){
  //    }
  encButPrevState = readingEncButState;
  //delay(responseDelay);

  //the rotary part.
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    //Serial.println(newPosition);
  }



}
