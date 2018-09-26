/*
Allegro A3967 based EasyStepper board
*/
int dirPin = 2;
int stepperPin = 3;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
}

void step(boolean dir,int steps){
  digitalWrite(dirPin,dir);
  delay(50);
  for(int i=0;i<steps;i++){
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(1500);
  }
}

void loop(){
  step(true,1000);
  delay(500);
  step(false,1000);
  delay(500);
}

