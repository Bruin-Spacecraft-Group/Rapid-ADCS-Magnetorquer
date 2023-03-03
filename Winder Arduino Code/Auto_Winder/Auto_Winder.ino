#define DIR_WINDER 1
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

// length of core, mm
double windLength = 70;
// wire gauge
int wireGauge = 32;

// mm
double wireDiameter = 8.247 * exp(-0.1159 * wireGauge);
double stepsPerWind = wireDiameter / (2.0 / (200.0 / 0.25));

void setup() {
  pinMode(DIR_WINDER, OUTPUT);
  pinMode(STEP_WINDER, OUTPUT);
  pinMode(DIR_SLIDER, OUTPUT);
  pinMode(STEP_SLIDER, OUTPUT);
  pinMode(SPEED_IN, INPUT);

  pinMode(MS1_WINDER, OUTPUT);
  pinMode(MS2_WINDER, OUTPUT);
  pinMode(MS3_WINDER, OUTPUT);

  Serial.begin(9600);
}

void setWinderPos(double mm){
  stepsPerWind = wireDiameter / (2.0 / (200.0 / 0.25));
  if(winderPos != stepsPerWind * mm){
    if(winderPos > stepsPerWind * mm){
      digitalWrite(DIR_WINDER, HIGH);
      digitalWrite(STEP_WINDER, HIGH);
      delay(1);
      digitalWrite(STEP_WINDER, LOW);
      delay(1);
      winderPos--;
    }
    else{
      digitalWrite(DIR_WINDER, HIGH);
      digitalWrite(STEP_WINDER, HIGH);
      delay(1);
      digitalWrite(STEP_WINDER, LOW);
      delay(1);
      winderPos++;
    }
  }
}

void loop() {
  int val = analogRead(SPEED_IN);
  double desiredPos = (((double) val) / 1024.0) * windLength;
  setWinderPos(desiredPos);
}
