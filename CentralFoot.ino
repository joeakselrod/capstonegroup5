//Joseph Akselrod rev 0.2.4
//2-18-21
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

//Create BLE attribure profile (ATT)for central
//Create Services for read left
//assign characteristics for corresponding services


//Helper functions
void getPeriph(char serviceUuid[], char streamUuid][], char calibrateUuid[])
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
    if (peripheral.advertisedServiceUuid() == serviceUuid) 
    {
      // stop scanning
      BLE.stopScan();
      //subscribe to the characteristics of the peripheral
      BLECharacteristic simpleKeyCharacteristic = peripheral.characteristic(calibrateUuid);
        // subscribe to the simple key characteristic
    Serial.println("Subscribing to simple key characteristic ...");
     if (!simpleKeyCharacteristic) {
      Serial.println("no simple key characteristic found!");
      peripheral.disconnect();
      return;
      } else if (!simpleKeyCharacteristic.canSubscribe()) {
    Serial.println("simple key characteristic is not subscribable!");
    peripheral.disconnect();
    return;
  } else if (!simpleKeyCharacteristic.subscribe()) {
    Serial.println("subscription failed!");
    peripheral.disconnect();
    return;
  } else {
    Serial.println("Subscribed");
    Serial.println("Press the right and left buttons on your SensorTag.");
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
   Serial.begin(9600);
  while (!Serial);
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("BLE Central - Peripheral Explorer");
  // start scanning for peripherals
  BLE.scan();
  //get correct peripheral and subscribe to its characteristics
  getPeriph("4b072a8c-447a-4552-a49f-3fc072368892",left_stream_uuid, left_calibration_uuid);
  BLE.scan();
  getPeriph("f71ffde7-c9da-434d-9cc9-eb25834cb67a");

}



void loop() 
{

}
