#include <Arduino.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)      // Arduino UNO
    #include <AltSoftSerial.h>
    AltSoftSerial bc95serial;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)   // Arduino MEGA2560
    #define bc95serial Serial1
#endif

#include "BC95Udp.h"
#include "MicrogearNB.h"

#define APPID   "TheBlackBox"
#define KEY     ""
#define SECRET  ""

BC95UDP client;
Microgear mg(&client);

char payload[32];
int i;
bool ledStatus = false;

void setup() {
    bc95serial.begin(9600);
    BC95.begin(bc95serial);
    BC95.reset();
    
    Serial.begin(9600);
    Serial.println(F("Microgear Arduino NB-IoT Start!"));
    Serial.print(F("IMEI: "));
    Serial.println(BC95.getIMEI());
    Serial.print(F("IMSI: "));
    Serial.println(BC95.getIMSI());

    Serial.print(F("Attach Network..."));
    while (!BC95.attachNetwork()) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(F("\nNB-IOT attached!"));
    Serial.print(F("RSSI: "));
    Serial.println(BC95.getSignalStrength());
    Serial.print(F("IPAddress: "));
    Serial.println(BC95.getIPAddress());

    mg.init(APPID, KEY, SECRET);
    mg.begin(5555);
}

void loop() {
    Serial.print(i);
    Serial.print(" ");
    Serial.println(ledStatus);
    mg.publish("/dataTag",(char)i); delay(10);
    mg.publish("/ledStatus/one", !ledStatus); delay(10);
    mg.publish("/ledStatus/two", !ledStatus); delay(10);
    mg.publish("/ledStatus/three", !ledStatus); delay(10);
    
    if(i == 0)
    {
      mg.writeFeed("HappyIoTFeed", "manCount:10.00"); 
    }
    else if(i == 1)
    {
      mg.writeFeed("HappyIoTFeed", "manCount:2.00"); 
    }
    else if(i == 2)
    {
      mg.writeFeed("HappyIoTFeed", "manCount:4.00"); 
    }
    else if(i == 3)
    {
      mg.writeFeed("HappyIoTFeed", "manCount:6.00"); 
    }
    else if(i == 4)
    {
      mg.writeFeed("HappyIoTFeed", "manCount:8.00"); 
    }
    
    i++;
    i = i%5;
    ledStatus = !ledStatus;
    mg.loop();
    delay(20000);
}
