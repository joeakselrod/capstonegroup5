
#include <ArduinoBLE.h>
int sensorPin = A0;    // pressure transducer sensor pin
int select = D2;
int userWeight = 0;
int reset == false;

void setup() 
{
  pinMode(sensorPin, INPUT);
  pinMode(select, INPUT);
}

void loop() 
{
  
  //start device while user is standing
 if(digitalRead(select)== HIGH)
  userWeight = analogRead(sensorPin);
 delay(3000);
 if(digitalRead(select) == HIGH)
 //user begins seated
 while((reset == true) && (analogRead(sensorPin == true))
 {
 
}
