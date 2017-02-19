/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = LOW;         // variable for reading the pushbutton status
int prevLatchingButState = LOW;
int readingLatchingButState = LOW;
long debounce2 = 20;

long time = 0;
void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  readingLatchingButState = digitalRead(buttonPin);
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
/*
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (readingLatchingButState == HIGH && prevLatchingButState == LOW && millis() - time > debounce2) {
    if(buttonState == HIGH){
    // turn LED on:
    buttonState = LOW;
    digitalWrite(ledPin, HIGH);
    //Serial.println(buttonState);
    Serial.println("not triggerred");
    }else{
      buttonState = HIGH;
      Serial.println("triggerred");
    }
    time = millis();
  } 
  prevLatchingButState = readingLatchingButState;
  */
}
