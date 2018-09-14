/*
IBT-2 Motor Control Board driven by Arduino.
 
Speed and direction controlled by a potentiometer attached to analog input 0.
One side pin of the potentiometer (either one) to ground; the other side pin to +5V
 
Connection to the IBT-2 board:
IBT-2 pin 1 (RPWM) to Arduino pin 5(PWM)
IBT-2 pin 2 (LPWM) to Arduino pin 6(PWM)
IBT-2 pins 3 (R_EN), 4 (L_EN), 7 (VCC) to Arduino 5V pin
IBT-2 pin 8 (GND) to Arduino GND
IBT-2 pins 5 (R_IS) and 6 (L_IS) not connected
*/
int RPWM_Output1 = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output1 = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
int RPWM_Output2 = 7; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output2 = 8; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
 
void setup()
{
  Serial.begin(9600);
  pinMode(RPWM_Output1, OUTPUT);
  pinMode(LPWM_Output1, OUTPUT);
  pinMode(RPWM_Output2, OUTPUT);
  pinMode(LPWM_Output2, OUTPUT);
}
void loop()
{
   if (Serial.available())                        //Make sure all the frame is received
  {
    char val = Serial.read();
    // sensor value is in the range 0 to 1023
    // the lower half of it we use for reverse rotation; the upper half for forward rotation
    if (val == 'f')
    {
      Serial.println("forward");
      analogWrite(LPWM_Output1, 50);
      analogWrite(RPWM_Output1, 0);
      analogWrite(LPWM_Output2, 35);
      analogWrite(RPWM_Output2, 0);
    }
    else if(val == 'b')
    {
      Serial.println("back");
      analogWrite(LPWM_Output1, 0);
      analogWrite(RPWM_Output1, 50);
      analogWrite(LPWM_Output2, 0);
      analogWrite(RPWM_Output2, 35);
    }
    else if(val == 's')
    {
      Serial.println("stop");
      analogWrite(LPWM_Output1, 0);
      analogWrite(RPWM_Output1, 0);
      analogWrite(LPWM_Output2, 0);
      analogWrite(RPWM_Output2, 0);
    }
  }

}

