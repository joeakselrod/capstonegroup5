//Joseph Akselrod rev 0.2
//left foot peripheral device 

#include <ArduinoBLE.h>
#include <Filters.h>

//define uuid for all services/characteristics 
const String left_foot_uuid = "4b072a8c-447a-4552-a49f-3fc072368892";
const String standing_distance_uuid = "876e1475-1fec-4a95-be64-d1b634f35511";
const String standing_weight_uuid = "9a53caac-1cbe-44e8-8502-8102f7883302";
const String sitting_weight_uuid = "91e9495d-7866-4b26-a6b1-17737d1f4e89";
const String calibration_uuid = "6532b055-f7ae-4a16-b551-93b58af62518";

int sensorPin = A0;   //Pressure transducer sensor pin
int select = D2;      //Calibration select button (stand>push>wait>sit>push>wait)
int standW = 0;       //user standing weight (for calibration)
int sitW = 0;         //user sitting weight (for calibration)
int distance = 0;
int oldCalibrationData = 0;
int oldStandingDistance = 0;
int oldStandingWeight = 0;

//Create BLE attribure profile (ATT)
//Create Services for calibration and datastream
//assign characteristics for corresponding services
BLEService leftFoot(left_foot_uuid);  //should be 128 bit random generated uuid; fuck it for now
BLEIntCharacteristic standingDistance(standing_distance_uuid, BLEWrite);  
BLEIntCharacteristic standingWeight(standing_weight_uuid, BLEWrite);
BLEIntCharacteristic sittingWeight(sitting_weight_uuid, BLEWrite);
BLEIntCharacteristic calibration(calibration_uuid, BLEWrite);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Helper Functions below here*/
void calibrate()
{
  //get standing weight, standing RSSI(distance), then sitting weight
  Serial.print("please stand normally and press toggle button");
  if(digitalRead(select)== HIGH)
  {
    int standW = getStandingWeight();
    int distance = getStandingRssi();
  }
  delay(1500);
  Serial.print("Now sit down and press button; program will start 1 second after.");
  if(digitalRead(select) == HIGH)
    int sitW = getSittingWeight();
  delay(1500);
  String calibrationData = String(standW + sitW + distance);  //send calibration data as a string and parse it in python
    if (calibrationData != oldCalibrationData) //if cal data is changed
    {      
      Serial.print("Calibration data is: "); // print it
      Serial.println(calibrationData);
      calibration.writeValue(calibrationData);  // and update the battery level characteristic
      oldCalibrationData = calibrationData;   
    }
}
void stream()
{
  Serial.print("Data stream to central: ");
  int standW = getStandingWeight();
  int distance = getStandingRssi();
  String streamData = String(standW + distance);  //send calibration data as a string and parse it in python
  if (streamData != oldStreamData) //if stream data is changed
    {      
      Serial.print("Stream data is: "); // print it
      Serial.println(StreamData);
      stream.writeValue(streamData);  // and update the battery level characteristic
      oldStreamData = streamData;   
    }
}
int getStandingWeight()
{
  return(analogRead(sensorPin));
}
int getStandingRssi()
{
  //use HC-05 to get RSSI data from Right foot HC05
}
int getSittingWeight()
{
  return(analogRead(sensorPin));
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
    //serial baud rate at 9600 bps
  Serial.begin(9600);
 
    //set pinmode
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(sensorPin, INPUT);
  pinMode(select, INPUT);


    //initialize BLE  
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("Advertising to central...");

  BLE.setLocalName("Left_Foot");
  BLE.setAdvertisedService(leftFoot); // add the service UUID
  leftFoot.addCharacteristic(calibration); // add the battery level characteristic
  leftFoot.addCharacteristic(standingDistance);
  leftFoot.addCharacteristic(standingWeight);
  BLE.addService(leftFoot); // Add the service
  calibrationData.writeValue(oldCalibrationData); // set initial value for this characteristic
  standingDistance.writeValue(oldStandingDistance);
  standingWeight.writeValue(oldStandingWeight);
  
  BLE.advertise();
  
}
  

}
void loop() 
{

  BLEDevice central = BLE.available();

  if (central) {
    Serial.print("Connected to central: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    // while the central is connected:
    while(central.connected())
    {
      //find and tx calibration data
        calibrate();
        delay(2000);
      //tx sensor and RSSI data (potentially accelerometer) as stream
        stream();  
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");

  }
}
