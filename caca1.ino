//Joseph Akselrod rev 0.1
//left foot peripheral device 

#include <ArduinoBLE.h>
#include <Filters.h
int sensorPin = A0;   //Pressure transducer sensor pin
int select = D2;      //Calibration select button (stand>push>wait>sit>push>wait)
int standW = 0;       //user standing weight (for calibration)
int sitW = 0;         //user sitting weight (for calibration)
int reset == false;

//Create BLE attribure profile (ATT)
//Create Services for calibration and datastream
//assign characteristics for corresponding services
BLEService leftFootCal("FB01");  //should be 128 bit random generated uuid; fuck it for now
BLEIntCharacteristic standingDistance("C6B6", BLERead);  
BLEIntCharacteristic standingWeight("A363", BLENotify);
BLEIntCharacteristic sittingWeight("C365", BLENotify);

BLEService leftFootStream("cacaballs");
BLEIntCharacteristic currentWeight("C6B6", BLERead);  


void setup() 
{
  Serial.begin(9600);
  while(!Serial);       //wait
  
  //sensor pin and select buttons are inputs
  pinMode(sensorPin, INPUT);
  pinMode(select, INPUT);

  //begin BLE
  BLE.begin();
  if(periConnect() == true)
  {
    BLE.stopScan();
    
  }
  BLE.setEventHandler(BLEDiscovered, discovered);
  
  
  

}

//
bool periConnect(){
  BLE.scan();
  BLEDevice peripheral = BLE.available();
    if (peripheral) 
      {
        Serial.print("found");
        if(peripheral.advertisedServiceUuid() = "xx.yy.zz...")
          return true;
      }
}
int getRssi()
{
  
}
bool centConnect(){
  BLE.advertise();
  
}


void loop() 
{
  //constant sense rssi from right
  //trigger: left senses step
  //stop rssi from right
  //tx rssi to central

  //if this shit doesnt work i swear to fuckin god i will hang myself
 
 //start device while user is standing
 if(digitalRead(select)== HIGH)
    standW = analogRead(sensorPin);
 delay(3000);
 //user sits down
 if(digitalRead(select) == HIGH)
    sitW = analogRead(sensorPin);
 delay(1000);
 while(
 //Calibration is complete; begin calibration packet tx
 /////////////////////////////////////////////////////////////////
}
