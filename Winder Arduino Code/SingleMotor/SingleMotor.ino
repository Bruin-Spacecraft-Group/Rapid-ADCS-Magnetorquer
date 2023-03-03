#define DIR 13
#define STEP 3
#define SPEED_IN A0
#define MS1 5
#define MS2 6
#define MS3 7

// THIS CODE ONLY RUNS ONE STEPPER MOTOR

// CONNECTIONS:
// Connect direction and step pins on controller as defined above
// Connect speed divider selection on controller as defined above
// Connect pot with output on SPEED_IN

// USE:
// Moving the pot will cause the motor to spin either forward or backwards, at varying speeds 
// depending on the amount of twist.
// There is a deadzone in the middle where the motor does not spin--it also prints out the
// number of rotations completed at this time.

boolean FULL[3] = {0,0,0};
boolean HALF[3] = {1,0,0};
boolean QUARTER[3] = {0,1,0};
boolean EIGHTH[3] = {1,1,0};
boolean SIXTEENTH[3] = {1,1,1};
int values[5] = {450,350,250,150,50};
double CW = 1;
double speed = 500;
double speedMax = 1200;
double stepCount = 0;
double rotations = 0;
double val = 0;
double deadzone = 50;

long long counter = 0;

boolean isHigh = true;
double divider = 1;

void setup() {
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(SPEED_IN, INPUT);

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  Serial.begin(9600);
  counter = 0;
}

void setStepSize(boolean ONE, boolean TWO, boolean THREE){
  if(ONE){
    digitalWrite(MS1, HIGH);
  }
  else{
    digitalWrite(MS1, LOW);
  }
  if(TWO){
    digitalWrite(MS2, HIGH);
  }
  else{
    digitalWrite(MS2, LOW);
  }
  if(THREE){
    digitalWrite(MS3, HIGH);
  }
  else{
    digitalWrite(MS3, LOW);
  }
}

void loop() {
  val = analogRead(SPEED_IN) - 512.0;
  if(val < 0){
    if(isHigh){
      CW = 1;
      Serial.println("went low");
      digitalWrite(DIR, LOW);
      isHigh = false;
    }
  }
  else{
    if(!isHigh){
      CW = -1;
      Serial.println("went high");
      digitalWrite(DIR, HIGH);
      isHigh = true;
    }
  }
  val = abs(val);
  if(val > values[0]){
    setStepSize(FULL[0], FULL[1], FULL[2]);
    divider = 1;
  }
  else if(val > values[1]){
    setStepSize(HALF[0], HALF[1], HALF[2]);
    divider = 0.5;
  }
  else if(val > values[2]){
    setStepSize(QUARTER[0], QUARTER[1], QUARTER[2]);
    divider = 0.25;
  }
  else if(val > values[3]){
    setStepSize(EIGHTH[0], EIGHTH[1], EIGHTH[2]);
    divider = 0.125;
  }
  else if(val > values[4]){
    setStepSize(SIXTEENTH[0], SIXTEENTH[1], SIXTEENTH[2]);
    divider = 0.0625;
  }
  if(val > deadzone){
    stepCount += CW * divider;
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
  }
  else{
    Serial.println((double) stepCount / 200.0);
  }
  delay(1);
}
