double count = 0; //set the counts of the encoder
double angle = 0; //set the angles
boolean A,B;
byte state, statep;

double pwm = 9;// this is the PWM pin for the motor for how much we move it to correct for its error
const int dir1 = 6;//these pins are to control the direction of the motor (clockwise/counter-clockwise)
const int dir2 = 5;

double setpoint = 200;  //3072;//I am setting it to move through 100 degrees
double Kp = 0.09;  //0.015;// you can set these constants however you like depending on trial & error
double Ki = 0.000071;//0.000109;
double Kd = 0.0; //0.93866;  //0.1009;

float last_error = 0;
float error = 0;
float changeError = 0;
float totalError = 0;
float pidTerm = 0;
float pidTerm_scaled = 0;// if the total gain we get is not in the PWM range we scale it down so that it's not bigger than |255|


void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP); //encoder pins
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),Achange,CHANGE);//interrupt pins for encoder
  attachInterrupt(digitalPinToInterrupt(3),Bchange,CHANGE); 
  pinMode(pwm, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
}

void loop(){
  
  PIDcalculation();// find PID value
  
  if (angle < setpoint) {
    digitalWrite(dir1, LOW);// Forward motion
    digitalWrite(dir2, HIGH);
  } else {
    digitalWrite(dir1, HIGH);//Reverse motion
    digitalWrite(dir2, LOW);
  }

  analogWrite(pwm, pidTerm_scaled);

  //Serial.println("WHEEL ANGLE:");
  Serial.print(setpoint);
  Serial.print(" ");
  Serial.println(angle);
  
  //delay(100);
}

void PIDcalculation(){
  /* 
   *  angle = ( 0.1171875 * count);//count to angle conversion = 360/(64*12*4)
   *  reduction ratio: 64:1 , pulses per revolution: 12CPR
  */
  
  angle = ( 0.45 * count);
  error = setpoint - angle;
  
  changeError = error - last_error; // derivative term
  totalError += error; //accumalate errors to find integral term
  pidTerm = (Kp * error) + (Ki * totalError) + (Kd * changeError);//total gain
  pidTerm = constrain(pidTerm, -255, 255);//constraining to appropriate value
  pidTerm_scaled = abs(pidTerm);//make sure it's a positive value

  last_error = error;
}
  
void Achange() //these functions are for finding the encoder counts
{
  A = digitalRead(2);
  B = digitalRead(3);
/*
  Serial.print(A);
  Serial.print("      ");
  Serial.println(B); */
  if ((A==HIGH) && (B==HIGH)) state = 1;
  if ((A==HIGH) && (B==LOW) ) state = 2;
  if ((A==LOW)  && (B==LOW) ) state = 3;
  if ((A==LOW)  && (B==HIGH)) state = 4;
  switch (state)
  {
    case 1:
    {
      if (statep == 2) count++;
      if (statep == 4) count--;
      break;
    }
    case 2:
    {
      if (statep == 1) count--;
      if (statep == 3) count++;
      break;
    }
    case 3:
    {
      if (statep == 2) count --;
      if (statep == 4) count ++;
      break;
    }
    default:
    {
      if (statep == 1) count++;
      if (statep == 3) count--;
    }
  }
  statep = state;

}

void Bchange()
{
  A = digitalRead(2);
  B = digitalRead(3);
    
  if ((A==HIGH) && (B==HIGH)) state = 1;
  if ((A==HIGH) && (B==LOW) ) state = 2;
  if ((A==LOW)  && (B==LOW) ) state = 3;
  if ((A==LOW)  && (B==HIGH)) state = 4;
  switch (state)
  {
    case 1:
    {
      if (statep == 2) count++;
      if (statep == 4) count--;
      break;
    }
    case 2:
    {
      if (statep == 1) count--;
      if (statep == 3) count++;
      break;
    }
    case 3:
    {
      if (statep == 2) count --;
      if (statep == 4) count ++;
      break;
    }
    default:
    {
      if (statep == 1) count++;
      if (statep == 3) count--;
    }
  }
  statep = state;
  
}
