/* Arduino Stepper Control with Potentiometer

Created by Yvan / https://Brainy-Bits.com
This code is in the public domain...
You can: copy it, use it, modify it, share it or just plain ignore it!
Thx!

*/

#include "AccelStepper.h" 
// Library created by Mike McCauley at http://www.airspayce.com/mikem/arduino/AccelStepper/

// AccelStepper Setup
AccelStepper stepper(1, 3, 2);    // 1 = Easy Driver interface
                                  // Nano Pin 3 connected to STEP pin of Easy Driver
                                  // Nano Pin 2 connected to DIR pin of Easy Driver

// Variables to store current, previous and move position
int val = 0;
int previous = 0;
int long newval = 0;    

void setup() 
{
  Serial.begin(9600);
  stepper.setMaxSpeed(2400);  // Set speed fast enough to follow pot rotation
  stepper.setAcceleration(2400);  //  High Acceleration to follow pot rotation
  previous = analogRead(A4);  
  Serial.print("Init previous");
  Serial.println(previous);
}

void loop() 
{
  val = analogRead(A4);      //  Read Potentiometer current value
  if (Serial.available())    //  Make sure all the frame is received
  {
    char cmd = Serial.read();
    if (cmd == 'l')
    {
      Serial.println("serial left");
      previous = previous+20;
      cmd = 'z';
    }
    else if (cmd == 'r')
    {
      Serial.println("serial right");
      previous = previous-20;
      cmd = 'z';
    }
  }
  
  if ((val > previous+10) || (val < previous-10)) // Check that a move of the pot is at least > or < than 6
  {  
    newval = map(val, 0, 1023, 0, 1600);        // Map value (1600 = 1 stepper shaft rotation)
    stepper.runToNewPosition(newval);  // Move stepper to new position
    previous = val;  // save current value into variable previous
    
    Serial.print("newval");
    Serial.println(newval);
    Serial.print("previous");
    Serial.println(previous);
  }
}
