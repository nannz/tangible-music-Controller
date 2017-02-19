int fsrPin = A1;
int fsrReading;

int curFsrState = LOW;
int prevFsrState = LOW;

long fsrDownTime = -1;
long fsrUpTime = -1;
long time = 0;
int fsrHoldTime = 100; // ms hold period: how long to wait for press+hold event
int fsrLongHoldTime = 2000; // ms long hold period: how long to wait for press+hold event

void setup() {
  Serial.begin(9600);

}

void loop() {
  fsrReading = analogRead(fsrPin);
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);     // the raw analog reading

  if (fsrReading == 0) {
    curFsrState = LOW;
  } else {
    curFsrState = HIGH;
  }

  if (curFsrState == HIGH && prevFsrState == LOW) {
    //press down
    fsrDownTime = millis();
    Serial.print("fsrDownTime: ");
    Serial.println(fsrDownTime);
  }
  if (curFsrState == LOW && prevFsrState == HIGH){
    //press up
    fsrUpTime = millis();
    Serial.print("fsrUpTime: ");
    Serial.println(fsrUpTime);
  }
  if (curFsrState == LOW && prevFsrState == HIGH ) {
    if((fsrUpTime - fsrDownTime) >= fsrHoldTime){
      if ((fsrUpTime - fsrDownTime) >= fsrLongHoldTime){
        Serial.println("long pressed");
      }else{
        Serial.println("clicked");
      }    
    }   
  }
  prevFsrState = curFsrState;


}
