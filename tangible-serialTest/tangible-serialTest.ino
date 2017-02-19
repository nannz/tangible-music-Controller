int potPin = A0;
int potenVal = 0;
int previousPotenVal = 0;

const int switchPin = 2;
int previousSwitch = LOW;
int readingSwitch;           // the current reading from the input pin
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

int toggleSwitchPin = 3;
int readingToggle = 0;
int previousToggle = 0;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
}

void loop() {
  readingSwitch = digitalRead(switchPin);
  potenVal = analogRead(potPin);
  readingToggle = digitalRead(toggleSwitchPin);
  
  //Serial.println(readingToggle);
  
  if(readingToggle == 0 && previousToggle == 1 && millis() - time > debounce){
    Serial.write(54); //normal speed
    time = millis();
  }else if(readingToggle == 1 && previousToggle == 0 && millis() - time > debounce){
    Serial.write(53); //fast
    time = millis();
  }

  
  if (readingSwitch == LOW && previousSwitch == HIGH && millis() - time > debounce) {
    Serial.write(49);
    time = millis();
  }

  previousSwitch = readingSwitch;
  previousToggle = readingToggle;
  delay(1);


}


