
/* 
 *  
 *  https://www.instructables.com/id/Wiper-Motor-and-Arduino-Mega-Servo/
 *  
 */
 
#include "MegaServo.h"
MegaServo megaServo;

void setup()
{
  Serial.begin(115200);   
  megaServo.attach(7, 8, 5, A4);
  megaServo.write(90);
}

void loop()
{
  if (Serial.available())
  {
    int angle = Serial.parseInt();
    Serial.println(angle);
    if(angle > 0 && angle < 180)
    {
      megaServo.write(angle);
    }
  }
}
