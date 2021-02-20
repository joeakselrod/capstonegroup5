// A0 - pin 8
// RX - pin 16
// TX - pin 17

int analogPin = 8;
int data = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){
  data = analogRead(analogPin);
  Serial.println(data);
  delay(10);
}
