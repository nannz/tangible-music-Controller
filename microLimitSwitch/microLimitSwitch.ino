

int microSwitchInPin = 2;         // the number of the input pin
int switchState = LOW;      // the current state of the output pin
int readingSwitch;           // the current reading from the input pin
int previousSwitch = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

void setup() {
  Serial.begin(9600);
  pinMode(microSwitchInPin, INPUT);
}

void loop() {
  readingSwitch = digitalRead(microSwitchInPin);
  if (readingSwitch == HIGH && previousSwitch == LOW && millis() - time > debounce) {
    if (switchState == HIGH) {
      switchState = LOW;
      Serial.println(switchState);
    } else {
      switchState = HIGH;
      Serial.println(switchState);
    }
    time = millis();
  }
  
}

