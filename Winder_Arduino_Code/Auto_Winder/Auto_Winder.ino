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

boolean isForwardSlider = 1;
boolean isForwardWinder = 1;
long stepsTaken = 0;
double deadzone = 0.1;

// length of core, mm
int windLength = 70;
// wire gauge
int wireGauge = 32;

// mm
double wireDiameter = 8.247 * exp(-0.1159 * wireGauge);

// Slider is kept at EIGHTH speed (400 steps / mm)
// Winder is kept at FULL speed (50 steps / rotation)

double stepsWinderPerSlider = 4.0 / wireDiameter;
double stepsBehind = 0;

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

double val = 0;
int timeDelay = 1000;

void loop() {
  val = ((((double) analogRead(SPEED_IN)) / 1024.0) - 0.5); // value from -0.5 to 0.5
  if(abs(val) > 0.25){
    timeDelay = 3000;
  }
  else{
    timeDelay = 100;
  }
  int currentVal = (stepsTaken / 2 + 200 * windLength)%(400 * windLength) - 200 * windLength;
  
  if(abs(val) > deadzone){
    digitalWrite(STEP_SLIDER, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(STEP_SLIDER, LOW);
    if(val < 0){
      stepsTaken--;
      stepsBehind -= stepsWinderPerSlider;
      currentVal *= -1;
    }
    else{
      stepsTaken++;
      stepsBehind += stepsWinderPerSlider;
    }
    if(stepsBehind > 0){
      while(stepsBehind >= 1){
        digitalWrite(STEP_WINDER, HIGH);
        delayMicroseconds(50);
        digitalWrite(STEP_WINDER, LOW);
        delayMicroseconds(50);
        stepsBehind -= 1.0;
      }
    }
    else if(stepsBehind < 0){
      while(stepsBehind <= -1){
        digitalWrite(STEP_WINDER, HIGH);
        delayMicroseconds(50);
        digitalWrite(STEP_WINDER, LOW);
        delayMicroseconds(50);
        stepsBehind += 1.0;
      }
    }
  }
  
  if(currentVal > 0){
    if(!isForwardSlider){
      digitalWrite(DIR_SLIDER, HIGH);
      isForwardSlider = true;
    }
  }
  else{
    if(isForwardSlider){
      digitalWrite(DIR_SLIDER, LOW);
      isForwardSlider = false;
    }
  }
  if(val > 0){
    if(!isForwardWinder){
      digitalWrite(DIR_WINDER, HIGH);
      isForwardWinder = true;
    }
  }
  else{
    if(isForwardWinder){
      digitalWrite(DIR_WINDER, LOW);
      isForwardWinder = false;
    }
  }
}
