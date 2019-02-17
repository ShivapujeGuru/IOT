int incomingVehicles = 0;
int outgoingVehicles = 0;

//Proximity Sensor related pins in Arduino
int k = A0;

//second proximity sensor
int k1 = A1;

//third proximity sensor
int k2 = A2;


int D1 = 6;
int D2 = 7;
int D3 = 8;


//Rain sensor pin in Arduino
int RainIn = A5;
int RainVal;

//Ir sensor pins in Arduino
int IRsensor = A3;
int IRvalue;
int IR = 5;


//Ldr module pins in Arduino
int ldrSensor = A4;
int ldr = 4;
int ldrValue;

// Code to use SoftwareSerial
#include <SoftwareSerial.h>
SoftwareSerial espSerial =  SoftwareSerial(2, 3); // arduino RX pin=2  arduino TX pin=3    connect the arduino RX pin to esp8266 module TX pin   -  connect the arduino TX pin to esp8266 module RX pin

//1st argument in the above function is for tx of ESP9266 and 2nd argument in the above function is for RX


String apiKey = "9KP2OLGJ7BBODK5B";     // replace with your channel's thingspeak WRITE API key

String ssid = "cosmos";  // Wifi network SSID
String password = "streetlight";  // Wifi network password

boolean DEBUG = true;

//======================================================================== showResponce
void showResponse(int waitTime) {
  long t = millis();
  char c;
  while (t + waitTime > millis()) {
    if (espSerial.available()) {
      c = espSerial.read();
      if (DEBUG) Serial.print(c);
    }
  }

}

//========================================================================
boolean thingSpeakWrite() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";                  // TCP connection
  cmd += "184.106.153.149";                               // api.thingspeak.com
  cmd += "\",80";
  espSerial.println(cmd);
  if (DEBUG) Serial.println(cmd);
  if (espSerial.find("Error")) {
    if (DEBUG) Serial.println("AT+CIPSTART error");
    return false;
  }


  String getStr = "GET /update?api_key=";   // prepare GET string
  getStr += apiKey;

//  getStr += "&field1=900";
//  
////  getStr += String(incomingVehicles);
//  getStr += "&field2=200";
////  getStr += String(incomingVehicles - outgoingVehicles);
//  getStr += "&field3=400";
////  getStr += String(RainVal);
//  getStr += "&field4=444";
////  getStr += String(ldrValue);
//  getStr += "&field5=400";
////  getStr += String(IRvalue);
//getStr += "&field6=430";

  getStr += "&field1=100&field2=222&field3=100&field4=300&field5=400&field6=200";
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  espSerial.println(cmd);
  if (DEBUG)  Serial.println(cmd);

  delay(500);
  if (espSerial.find(">")) {
    espSerial.print(getStr);
    if (DEBUG)  Serial.print(getStr);
  }
  else {
    espSerial.println("AT+CIPCLOSE");
    // alert user
    if (DEBUG)   Serial.println("AT+CIPCLOSE");
    return false;
  }
  return true;
}



//================================================================================ setup
void setup() {
  DEBUG = true;         // enable debug serial
  Serial.begin(115200);



  espSerial.begin(115200);  // enable software serial
  // Your esp8266 module's speed is probably at 115200.
  // For this reason the first time set the speed to 115200 or to your esp8266 configured speed
  // and upload. Then change to 9600 and upload again

  espSerial.println("AT+RST");         // Enable this line to reset the module;
  showResponse(1000);

  espSerial.println("AT+UART_CUR=115200,8,1,0,0");    // Enable this line to set esp8266 serial speed to 9600 bps
  showResponse(1000);



  espSerial.println("AT+CWMODE=3");   // set esp8266 as client
  showResponse(1000);

  espSerial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\""); // set your home router SSID and password
  showResponse(5000);

  if (DEBUG)  Serial.println("Setup completed");


  //Proximity sensor Analog pins
  pinMode(k, INPUT);
  pinMode(k1, INPUT);
  pinMode(k2, INPUT);

  //Proximity Sensor light pins
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  //Rain Sensor Analog pin
  pinMode(RainIn, INPUT);


  //Ir sensor Analog pin
  pinMode(IRsensor, INPUT);

  //Ir sensor light pins
  pinMode(IR, OUTPUT);



  //Ldr module Analog pin
  pinMode(ldrSensor, INPUT);


  //ldr sensor light pin
  pinMode(ldr, OUTPUT);


}


// ====================================================================== loop
void loop() {
  //first proximty sensor
  //    int n = analogRead(k);
  //    Serial.print(n);
  //    if(n<800)
  //    {
  //      incomingVehicles++;
  //    }
  //    if(incomingVehicles>0)
  //    {
  //    digitalWrite(D1,HIGH);
  //    digitalWrite(D2,HIGH);
  //    }
  //    else
  //    {
  ////    delay(500);
  //    digitalWrite(D1,LOW);
  //    }
  //
  //second proximity just for displaying lights

  //    int p=analogRead(k1);
  //    if(count>0)
  //    {
  //    digitalWrite(D2,HIGH);
  //    delay(1000);
  //    }
  //
  //    else
  //    digitalWrite(D2,LOW);
  //



  //Third proximity sensor   discounts vehicles
  //  int m = analogRead(k2);
  //  Serial.print(m);
  //
  //  if(k2<800&&(incomingVehicles>0))
  //  {
  //    outgoingVehicles++;
  //    digitalWrite(D3,HIGH);
  ////    delay(500);
  //
  //    digitalWrite(D1,LOW);
  ////    delay(500);
  //    digitalWrite(D2,LOW);
  //  }
delay(1500);
  thingSpeakWrite();

//Rain sensor

//  RainVal = analogRead(RainIn);
//  Serial.print(RainVal);
//  /* if(RainVal>650)
//     {Serial.print("\n");
//     Serial.print("Heavy temperature\n");
//     }
//    else if (RainVal>400 && RainVal<650)
//     Serial.print("Normal temperature and No rain\n");
//    else if(RainVal>50 && RainVal<300)
//     Serial.print("Cloudy and Slow raining\n");
//    else if(RainVal<50)
//     Serial.print("Heavy Rain\n");*/
//
//
//  IRvalue = analogRead(IRsensor);
//  Serial.print(IRvalue);
//
//  /*if(IRvalue>300)
//    {
//      Serial.print("\n");
//      Serial.print("peoples are standing in bustop bus has to stop\n");
//      Serial.print("lights on \n");
//      digitalWrite(IR,HIGH);
//      }
//    else
//      {
//        Serial.print("peoples were not found");
//        digitalWrite(IR,LOW);
//        }
//  */
//
//
//  //ldr sensor values reading function
//  ldrValue = analogRead(ldrSensor);
//  Serial.print("ldr value\n");
//  Serial.print(ldrValue);
//
//  if (ldrValue > 1000)
//  {
//    digitalWrite(ldr, HIGH);
//  }
//  else
//  {
//    digitalWrite(ldr, LOW);
//  }

}





