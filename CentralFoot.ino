//Joseph Akselrod rev 0.2.7
//3-26-2021
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
  // start scanning for left foot peripheral by uuid
  BLE.scanForUuid("4b072a8c-447a-4552-a49f-3fc072368892");

    // check if a peripheral has been discovered
    BLEDevice leftFoot = BLE.available();

    if (leftFoot) {
      // discovered a peripheral, print out address, local name, and advertised service
      Serial.print("Found ");
      Serial.print(leftFoot.address());
      Serial.print(" '");
      Serial.print(leftFoot.localName());
      Serial.print("' ");
      Serial.print(leftFoot.advertisedServiceUuid());
      Serial.println();

        // stop scanning
        BLE.stopScan();
        //subscribe to the characteristics of the peripheral
        BLECharacteristic leftCalibrate = leftFoot.characteristic("6532b055-f7ae-4a16-b551-93b58af62518");

          // subscribe to the simple key characteristic
        Serial.println("Subscribing to calibrate characteristic ...");
        if (!leftCalibrate)
        {
          Serial.println("no calibrate characteristic found!");
          leftFoot.disconnect();
          return;
        }
        else if (!leftCalibrate.canSubscribe())
        {
          Serial.println("calibration characteristic is not subscribable!");
          leftFoot.disconnect();
          return;
        }
        else if (!leftCalibrate.subscribe())
        {
          Serial.println("subscription failed!");
          leftFoot.disconnect();
          return;
        }
        else
        {
          Serial.println("Subscribed");
        }
        // peripheral disconnected, we are done
        while (1)
        {
          // do nothing
        }


        //Now We subscribe to the left foot stream characteristic

        BLECharacteristic leftStream = leftFoot.characteristic("876e1475-1fec-4a95-be64-d1b634f35511");

          // subscribe to the simple key characteristic
        Serial.println("Subscribing to stream characteristic ...");
        if (!leftStream)
        {
          Serial.println("no stream characteristic found!");
          leftFoot.disconnect();
          return;
        }
        else if (!leftStream.canSubscribe())
        {
          Serial.println("stream characteristic is not subscribable!");
          leftFoot.disconnect();
          return;
        }
        else if (!leftStream.subscribe())
        {
          Serial.println("subscription failed!");
          leftFoot.disconnect();
          return;
        }
        else
        {
          Serial.println("Subscribed");
        }
        // peripheral disconnected, we are done
        while (1)
        {
          // do nothing
        }
     }




    //////////////////////////////////////////////////////////////////////////
    // start scanning for right foot peripheral by uuid
    //////////////////////////////////////////////////////////////////////////

    //right foot service
    BLE.scanForUuid("f71ffde7-c9da-434d-9cc9-eb25834cb67a");

      // check if a peripheral has been discovered
      BLEDevice rightFoot = BLE.available();

      if (rightFoot) {
        // discovered a peripheral, print out address, local name, and advertised service
        Serial.print("Found ");
        Serial.print(rightFoot.address());
        Serial.print(" '");
        Serial.print(rightFoot.localName());
        Serial.print("' ");
        Serial.print(rightFoot.advertisedServiceUuid());
        Serial.println();

        // see if peripheral is the one we are looking for based on uuid

          // stop scanning
          BLE.stopScan();
          //subscribe to the characteristics of the peripheral
          BLECharacteristic rightCalibrate = rightFoot.characteristic("88c51252-497b-46b7-80fd-926865f6169c");

            // subscribe to the simple key characteristic
          Serial.println("Subscribing to calibrate characteristic ...");
          if (!rightCalibrate)
          {
            Serial.println("no calibrate characteristic found!");
            rightFoot.disconnect();
            return;
          }
          else if (!rightCalibrate.canSubscribe())
          {
            Serial.println("calibration characteristic is not subscribable!");
            rightFoot.disconnect();
            return;
          }
          else if (!rightCalibrate.subscribe())
          {
            Serial.println("subscription failed!");
            rightFoot.disconnect();
            return;
          }
          else
          {
            Serial.println("Subscribed");
          }
          // peripheral disconnected, we are done
          while (1)
          {
            // do nothing
          }
          //////////////////////////////////////////////////////
          BLECharacteristic rightStream = rightFoot.characteristic("55e46e53-d546-49ee-be72-a2cbd47992f1");

            // subscribe to the simple key characteristic
          Serial.println("Subscribing to stream characteristic ...");
          if (!rightStream)
          {
            Serial.println("no stream characteristic found!");
            rightFoot.disconnect();
            return;
          }
          else if (!rightStream.canSubscribe())
          {
            Serial.println("stream characteristic is not subscribable!");
            rightFoot.disconnect();
            return;
          }
          else if (!rightStream.subscribe())
          {
            Serial.println("subscription failed!");
            rightFoot.disconnect();
            return;
          }
          else
          {
            Serial.println("Subscribed");
          }
          // peripheral disconnected, we are done
          while (1)
          {
            // do nothing
          }
       }

}



void loop()
{
  //calibrate data once
  Serial.println(leftFoot.leftCalibrate);
  Serial.println(rightFoot.rightCalibrate);

  //loop the streams
  while(1)
  {
    Serial.println(leftFoot.leftStream);
    Serial.println(rightFoot.rightStream);
   //serial print calibration data and then stream datastream
  }
}
