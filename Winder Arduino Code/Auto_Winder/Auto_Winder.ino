#define DIR_WINDER 13
#define STEP_WINDER 2
#define DIR_SLIDER 12
#define STEP_SLIDER 4
#define MS1_WINDER 5
#define MS2_WINDER 6
#define MS3_WINDER 7
#define SPEED_IN A0

boolean FULL[3] = {0,0,0};
boolean HALF[3] = {1,0,0};
boolean QUARTER[3] = {0,1,0};
boolean EIGHTH[3] = {1,1,0};
boolean SIXTEENTH[3] = {1,1,1};

boolean isForward = 1;
int timeDelay = 1000;
long stepsTaken = 0;
double deadzone = 0.05;

// length of core, mm
int windLength = 70;
// wire gauge
int wireGauge = 32;

// mm
double wireDiameter = 8.247 * exp(-0.1159 * wireGauge);

void setup() {
  pinMode(DIR_WINDER, OUTPUT);
  pinMode(STEP_WINDER, OUTPUT);
  pinMode(DIR_SLIDER, OUTPUT);
  pinMode(STEP_SLIDER, OUTPUT);
  pinMode(SPEED_IN, INPUT);

  pinMode(MS1_WINDER, OUTPUT);
  pinMode(MS2_WINDER, OUTPUT);
  pinMode(MS3_WINDER, OUTPUT);

  digitalWrite(MS1_WINDER, HIGH);
  digitalWrite(MS2_WINDER, HIGH);
  digitalWrite(MS3_WINDER, LOW);

  Serial.begin(9600);
}

void loop() {
  double val = ((((double) analogRead(SPEED_IN)) / 1024.0) - 0.5);
  double timeDelay = -3820.0 * pow(val, 2.0) + 1000.0;
  int currentVal = (stepsTaken / 2 + 200 * windLength)%(400 * windLength) - 200 * windLength;
  if(abs(val) > deadzone){
    digitalWrite(STEP_WINDER, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(STEP_WINDER, LOW);
    if(val < 0){
      stepsTaken--;
      currentVal *= -1;
    }
    else{
      stepsTaken++;
    }
  }
  if(currentVal > 0){
    if(!isForward){
      digitalWrite(DIR_WINDER, HIGH);
      isForward = true;
    }
  }
  else{
    if(isForward){
      digitalWrite(DIR_WINDER, LOW);
      isForward = false;
    }
  }
}
