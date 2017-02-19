
int potPin = A0; //Analog pin A0
int curPotenVal = 512; //value from the potenmeter
int prevPotenVal = 512;
bool potenState = false;

int responseDelay = 100;

int curPotenState = 0; //0 is stop, 1 is left, 2 is right
int prevPotenState = 4;


void setup() {

  Serial.begin(9600);
}

void loop() {
  curPotenVal = analogRead(potPin);
  //Serial.println(curPotenVal);

  if (curPotenVal - prevPotenVal < -1) { //to decrease the noise
    //turn left
    curPotenState = 1;
  } else if (curPotenVal - prevPotenVal > 1) {
    //turn right
    curPotenState = 2;
  } else {
    //not move
    curPotenState = 0;
  }
delay(responseDelay);
  if (curPotenState == 0 && prevPotenState == 1) { //play previous sone
    Serial.println("skip back");
  }
  if (curPotenState == 0 && prevPotenState == 2) {
    Serial.println("skip ahead");
  }
  //if now is stop and prev is left -> 前一首
  //if now is stop and prev is right -> 后一首

  prevPotenState = curPotenState;

  prevPotenVal = curPotenVal;

  //delay(responseDelay);

}
