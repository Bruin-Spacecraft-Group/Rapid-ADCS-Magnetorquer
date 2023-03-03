#define DIR_WINDER 13
#define STEP_WINDER 2
#define DIR_SLIDER 3
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

double winderPos = 0;
boolean isForward = 1;
double timePassed = 0;
int timeDelay = 1000;
long stepsTaken = 0;

// length of core, mm
int windLength = 70;
// wire gauge
int wireGauge = 32;

// mm
double wireDiameter = 8.247 * exp(-0.1159 * wireGauge);
double stepsPerWind = wireDiameter / (4.0 / (200.0 / 0.25));

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
  int val = analogRead(SPEED_IN);
  double timeDelay = sqrt((((double) val) / 1024.0) * 10000000 + 5);
  int currentVal = (stepsTaken / 2 + 200 * windLength)%(400 * windLength) - 200 * windLength;
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
  digitalWrite(STEP_WINDER, HIGH);
  delayMicroseconds(timeDelay);
  digitalWrite(STEP_WINDER, LOW);
  stepsTaken++;
}
