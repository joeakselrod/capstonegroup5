//Joseph Akselrod rev 0.2.6
//3-23-2021
//Central device

#include <ArduinoBLE.h>

//left foot UUIDs'
const char left_foot_uuid[] = "4b072a8c-447a-4552-a49f-3fc072368892";
const char left_stream_uuid[] = "876e1475-1fec-4a95-be64-d1b634f35511";
const char left_calibration_uuid[] = "6532b055-f7ae-4a16-b551-93b58af62518";

//right foot UUIDs
const char right_foot_uuid[] = "f71ffde7-c9da-434d-9cc9-eb25834cb67a";
const char right_stream_uuid[] = "55e46e53-d546-49ee-be72-a2cbd47992f1";
const char right_calibration_uuid[] = "88c51252-497b-46b7-80fd-926865f6169c ";

BLECharCharacteristic leftStream = NULL;
BLECharCharacteristic rightStream = NULL;


//Create BLE attribure profile (ATT)for central
//Create Services for read left
//assign characteristics for corresponding services



//Helper functions------------------------------------------------------------------------------------

//getPeriph() subscribes to a BLE service such as "leftStream" allows for automatic notification from peripheral to central
void getPeriph(BLEDevice peripheral, char *serviceUuid[], char *streamUuid, char *calibrateUuid, BLECharCharacteristic *stream, BLECharCharacteristic *calibrate)
{
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    // see if peripheral is a left or right based on the service uuid
    if (strcmp(peripheral.advertisedServiceUuid(), serviceUuid)==0)
    {
      // stop scanning
      BLE.stopScan();
      //subscribe to the characteristics of the peripheral
      BLECharCharacteristic calibrate = peripheral.characteristic(calibrateUuid);
      BLECharCharacteristic stream = peripheral.characteristic(streamUuid);
        // subscribe to the simple key characteristic
    Serial.println("Subscribing to calibrate characteristic ...");
     if (!simpleKeyCharacteristic) {
      Serial.println("no calibrate characteristic found!");
      peripheral.disconnect();
      return;
      } else if (!simpleKeyCharacteristic.canSubscribe()) {
    Serial.println("calibration characteristic is not subscribable!");
    peripheral.disconnect();
    return;
  } else if (!simpleKeyCharacteristic.subscribe()) {
    Serial.println("subscription failed!");
    peripheral.disconnect();
    return;
  } else {
    Serial.println("Subscribed");
  }
      // peripheral disconnected, we are done
      while (1)
      {
        // do nothing
      }
   }
  }
}

void setup()
{
  //baud rate
  Serial.begin(9600);

  while (!Serial);
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("BLE Central - Looking for peripherals...");
  // start scanning for peripherals
  BLE.scan();
  //get correct peripheral and subscribe to its characteristics
  getPeriph(leftFoot, left_foot_uuid, left_stream_uuid, left_calibration_uuid, leftStream, leftCalibrate);
  BLE.scan();
  getPeriph(rightFoot, right_foot_uuid, right_stream_uuid, right_calibration_uuid), rightStream, rightCalibrate;

}



void loop()
{
  //calibrate data once
Serial.println(leftCalibrate);
Serial.println(leftCalibrate);

  while(1)
  {
  Serial.println(leftStream);
  Serial.println(rightStream);
  //serial print calibration data and then stream datastream
  }
}
