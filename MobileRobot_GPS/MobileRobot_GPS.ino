#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial serialgps(2, 3);  // RX, Tx

int year;
byte month, day, hour, minute, second, hundredths;
unsigned long chars;
unsigned short sentences, failed_checksum;
float latitude, longitude;
int contLocalizacao = 0;

void send_data();

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600); 
  Serial2.begin(9600); 
  delay(5);  
}

void loop()
{ 
  sequenciaGPS(); 
  delay(10);
}

void sequenciaGPS()
{
  while (Serial1.available())
  {
    int c = Serial1.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&latitude, &longitude);
      send_data();
/*      
      Serial.print("Lat/Long: ");
      Serial.print(latitude, 5);
      Serial.print(",");
      Serial.println(longitude, 5);
      gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths);
      Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/");
      Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
      Serial.print(" Time: "); Serial.print(hour, DEC); Serial.print(":");
      Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC);
      Serial.print("."); Serial.println(hundredths, DEC);
      Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());
      Serial.print("Course (degrees): "); Serial.println(gps.f_course());
      Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
      Serial.print("Satellites: "); Serial.println(gps.satellites());
      Serial.println();
      gps.stats(&chars, &sentences, &failed_checksum);
*/
    }
  }
}

/********************************************/
/*               Sand Data                  */
/********************************************/

void send_data()                                
{
  String dataGPS = "#";
         dataGPS +=  String(latitude, 5);
         dataGPS += "|";
         dataGPS += String(longitude, 5);
         dataGPS += "|";
  Serial2.print(dataGPS);
}

/********************************************/
