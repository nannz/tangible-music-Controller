int fsrPin = A1;
int fsrReading;


void setup() {
 Serial.begin(9600);

}

void loop() {
  fsrReading = analogRead(fsrPin);  
 
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);     // the raw analog reading
}
