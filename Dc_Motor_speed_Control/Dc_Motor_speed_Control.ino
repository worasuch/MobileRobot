#include <PID_v1.h>

double kp = 0.99539;
double ki = 108.2584;
double kd = 0;
double Input = 0;
double Output = 0;
double Setpoint = 200;
double sampleRate = 1;
double t = 0;
double pi = 3.1415926;
int pinpwm = 5;
int en1 = 3;
int r = 0;

const byte interruptPin = 2;
volatile byte state = LOW;
PID aPID (&Input, &Output, &Setpoint,kp,kd,ki, DIRECT);

void setup() {
  Serial.begin(115200); //baud rate 9600 configuration
  //pinMode(38, INPUT); // reset digital to 4040 Counter after reading
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(pinpwm, OUTPUT); // PWM output
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), detect , RISING);//read counter by interrupt
  
  //aPID.SetMode(AUTOMATIC); // Turn on the PID loop as automatic control
  //aPID.SetSampleTime(sampleRate); // Sets the sample rate
}

void loop() {

  Input = r/t; // rps
  //Setting
  //Serial.print (Setpoint*pi*2);
  //Serial.print ("rpm");
  //Graph plotter
  Serial.print(Input*pi*2); //rad/s rate = 2pi rad * Input_rps
  Serial.print(" ");
  Serial.println(t);
  // End plotter
  aPID.Compute();
  analogWrite(pinpwm, Output);
  // put your main code here, to run repeatedly:*/

  Serial.println(r);

}

void detect() {
  r++;
}
