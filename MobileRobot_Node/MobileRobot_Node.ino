 
/***************************< File comment >***************************/  
/* project:   Mobile Robot Project                                    */ 
/* project description : -                                            */ 
/*--------------------------------------------------------------------*/ 
/* version : 1.0                                                      */ 
/* board : NodeMCU V.1                                                */ 
/* detail :                                                           */
/*--------------------------------------------------------------------*/ 
/* create : 27/08/2018                                                */ 
/* programmer : Worasuchad Haomachai                                  */ 
/**********************************************************************/ 

/* Fire base variable */
#include <FirebaseArduino.h>
#define FIREBASE_HOST "mobilerobotfirebase.firebaseio.com" //Database URL
#define FIREBASE_AUTH "jK9fhaCpgdiV5uSAg8mLSbJb1figwdVmFmehxCyT" // Firebase Secret
const String MobileRobot = "MobileRobot";
const String location = "/location";

/* Home variable */
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial chat(D5, D6); // RX, TX
/*
const char* ssid      = "FIBOROBOT_LAB";          //WiFi ssid name
const char* password  = "fiborobot_lab";          //password WiFi
*/
const char* ssid      = "iPhone/Happy";          //WiFi ssid name
const char* password  = "seams7373";             //password WiFi

boolean tagread = false;
String latitude, longitude;
char c[21];
uint32_t  FireBaseTimer;

void setup()
{
  chat.begin(9600);
  Serial.begin(9600);   //send data to computer
  Serial.println("Starting...");
  
  //initiate WiFi
  if (WiFi.begin(ssid, password))
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
  }
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  //initial Firebase
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  FireBaseTimer = millis();
}

void loop()
{
  if(chat.available() >= 19)                        
  {
    if(chat.read() == 0x23)
    {
      for(int i = 0; i < 19 ; ++i)
      {
        c[i] = chat.read();
      }
    }
  }
  
  for(int i = 0; i < 8 ; ++i)
  {
    latitude += c[i];
  }
  
  for(int i = 9; i < 18 ; ++i)
  {
    longitude += c[i];
  }
  
  if ((millis() - FireBaseTimer) >= 30000)    // send to firebase every 60s        
  {
    /*    fire base   */
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject&  valueObject = jsonBuffer.createObject();
    valueObject["latitude"] = latitude;
    valueObject["longitude"] = longitude;
    Firebase.push(MobileRobot + location , valueObject);
    FireBaseTimer = millis();
  }
  
  //Serial.print(latitude);
  //Serial.print(" ");
  //Serial.println(longitude);
  latitude = " ";
  longitude = " ";
  
}
