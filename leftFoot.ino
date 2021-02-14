//Joseph Akselrod rev 0.2.3
//2-14-21
//left foot peripheral device

#include <ArduinoBLE.h>
//#include <Filters.h>
#include <SoftwareSerial.h>
#include <Strings.h>

//define uuid for all BLE services/characteristics
const char* left_foot_uuid = "4b072a8c-447a-4552-a49f-3fc072368892";
const char* stream_uuid = "876e1475-1fec-4a95-be64-d1b634f35511";
const char* calibration_uuid = "6532b055-f7ae-4a16-b551-93b58af62518";

int sensorPin = A0;   //Pressure transducer sensor pin
int select = 2;      //Calibration select button (stand>push>wait>sit>push>wait)
//int standW = 0;       //default user standing weight (for calibration)
//int sitW = 0;         //default user sitting weight (for calibration)
//int distance = 0;     //default RSSI distance
char oldCalibrationData[] = "000000000";   //default calibration data
char oldStreamData[] = "0000000";
bool keepStreaming = true;

//Create BLE attribure profile (ATT)
//Create Services for calibration and datastream
//assign characteristics for corresponding services

BLEService leftFoot("4b072a8c-447a-4552-a49f-3fc072368892");  //should be 128 bit random generated uuid; fuck it for now
BLECharCharacteristic stream("876e1475-1fec-4a95-be64-d1b634f35511", BLEWrite);
BLECharCharacteristic calibration("6532b055-f7ae-4a16-b551-93b58af62518", BLEWrite);

//Setup Serial Communications to HC05
SoftwareSerial rssiBT(0,1); //rx and tx pins


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Helper Functions below here*/
char[] readRssiChar(int bufferSize)
{
  //convert the "rssiBT.readString" from type String to type char[]
  String string = rssiBT.readString();
  char buf[bufferSize];
  string.toCharArray(buf, bufferSize);
  return buf[];
}
char[] getWeight()
{
  char output[16];
  int num = analogRead(sensorPin)
  itoa(num, output, 10);
  return output[];
}

char[] getStandingRssi()
{
  char distance[] = "0000";
  //use HC-05 to get RSSI data from Right foot HC05
  //parse serial data and convert hex data
  char toBeParsed[] = readRssiChar(20);
  distance[] = serialParse(toBeParsed);
  return distance[];
}

char charConcat(int bufferSize, char firstChar[], char secondChar[])
{
  char buf[bufferSize];
  strcpy(buf,firstChar[]);
  strcat(buf,secondChar[]);
  return buf[];
}
char charConcat(int bufferSize, char firstChar[], char secondChar[], char thirdChar[])
{
  char buf[bufferSize];
  strcpy(buf,firstChar[]);
  strcat(buf,secondChar[]);
  strcat(buf,thirdChar[]);
  return buf[];
}
char serialParse(char array[])
{
  //THIS IS FUCKING DIFFICULT; SOMEONE HELP WE WITH THIS PLSSSSSS
  //Parse data from the RSSI serial o/p so we get just the rssi hex value

  //need to parse this > "+INQ:2:72:D2224,3E0104,FFBC"
  // to this > "FFBC"

  char *strings[10];
  char *ptr = NULL;
  int index = 0;
  ptr = strtok(array, ":,");              // takes a list of delimiters
  while(ptr != NULL)
  {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ":,");          // takes a list of delimiters
  }
  //print the last part of the string (second )
  //Serial.println(strings[5]);

  //play with strings[x] until we find correct data
  return strings[5];
}
void calibrates(char oldCalibrationData[])
{
  //get standing weight, standing RSSI(distance), then sitting weight
  //first get user to stand and press toggle button (select)
  Serial.print("please stand normally and press toggle button");
  if(digitalRead(select)== HIGH)  //if select is pressed
  {
    //get standing weight and RSSI distance
    char standW[] = getWeight();
    char distance[] = getStandingRssi();
  }
  delay(1500);
  //have user sit down and press select again
  Serial.print("Now sit down and press button; program will start a few seconds after.");
  if(digitalRead(select) == HIGH)
    char sitW[] = getWeight(); //gets sitting weight
  delay(1500);
  char calibrationData[] = charConcat(30, standW[], sitW[], distance[]);  //send calibration data as a string and parse it in python
    if (calibrationData != oldCalibrationData)                //if cal data is changed
    {
      Serial.print("Calibration data is: ");                  // print it
      Serial.println(calibrationData);
      calibration.writeValue(calibrationData);                //send data through BLE
      oldCalibrationData = calibrationData;                   // and update the calibration data
    }
}
void streams(char oldStreamData[])
{
  Serial.print("Data stream to central: ");
  //get current weight and RSSI data
  char standW[] = getWeight();
  char distance[] = getStandingRssi();
  char streamData[] = charConcat(30 , standW[], distance[]);  //send calibration data as a string and parse it in python
  if (streamData != oldStreamData) //if stream data is changed
    {
      Serial.print("Stream data is: ");           // print it
      Serial.println(StreamData);
      stream.writeValue(streamData);              //send data thru bLE
      oldStreamData = streamData;                 // and update the battery level characteristic
    }
}

void rssiBTSetup()
{
  //Setup Serial and BT connection for RSSI
  //Serial AT commands for rssi for inquired device
  bool loopINQ = true
  rssiBT.write("AT+INIT");   //initialize serial port profile
  //connect to specific BT address
  rssiBT.write("AT+BIND = 1234,56,abcdef");  //connect to address 12:34:56:ab:cd:ed
  delay(500);
  if(strcmp("OK", readRssiChar(4)) == 0)
    {
      rssiBT.write("AT+CLASS=0");
      rssiBT.write("AT+INQM = 1,2,48"); //set rssi inquiry for 2 devices up to 60 seconds
      //loop inquiry command so that we dont have timeout on the RSSI connection
      while(loopINQ == true)
      {
        rssiBT.write("AT+INQ"); //gets address, class, and RSSI in hex
        if(strcmp("OK", readRssiChar(4)) == 0);
        //if there is an "OK" when the serial o/p is finished with inq command, request inq again
        loopINQ = true;
      }
    }
   else
    {
      Serial.print("Connection to other HC05 failed");
    }


      //https://www.instructables.com/How-to-Configure-HC-05-Bluetooth-Module-As-Master-/
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
    //serial baud rate at 9600 bps
  Serial.begin(9600);
  rssiBT.begin(38400);  //Baud Rate for AT-command Mode.

    //set pinmode
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(select, INPUT);




    //initialize BLE
  if (!BLE.begin())
  {
    Serial.println("starting BLE failed!");
    while (1);
  }
  Serial.println("Advertising to central...");

  BLE.setLocalName("Left_Foot");
  BLE.setAdvertisedService(leftFoot);         // add the service UUID
  leftFoot.addCharacteristic(calibration);    // add the calibration characteristic
  leftFoot.addCharacteristic(stream);         // add the stream charcteristic
  BLE.addService(leftFoot);                   // Add the service
  calibration.writeValue(oldCalibrationData); // set initial value for calibration characteristic
  stream.writeValue(oldStream);               // set initial value for stream charcteristic
  BLE.advertise();                            // turn on transmission
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
        rssiBTSetup();
        calibrates(oldCalibrationData);
        delay(2000);
      //tx sensor and RSSI data (potentially accelerometer) as stream(loop)
        while(keepStreaming == true)
          streams(oldStreamData);
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
  }
}
