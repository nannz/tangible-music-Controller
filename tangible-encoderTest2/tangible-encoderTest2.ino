
int encButPin = 4;
int readingEncBut = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(encButPin, INPUT);
  Serial.println("Basic Encoder Test:");
}

void loop() {
  readingEncBut = digitalRead(encButPin);
  Serial.println(readingEncBut);
  
}
