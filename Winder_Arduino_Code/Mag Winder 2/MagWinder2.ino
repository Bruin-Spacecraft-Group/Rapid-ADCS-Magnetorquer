#define DIR_WINDER 4
#define STEP_WINDER 5

#define DIR_SLIDER 2
#define STEP_SLIDER 3

#define MS1_WINDER 1
#define MS2_WINDER 6
#define MS3_WINDER 7
#define MS1_SLIDER 10
#define MS2_SLIDER 9
#define MS3_SLIDER 8
#define SPEED_IN A0
#define BUTTON_1 A1
#define BUTTON_2 A2

boolean FULL[3] = {0, 0, 0};
boolean HALF[3] = {1, 0, 0};
boolean QUARTER[3] = {0, 1, 0};
boolean EIGHTH[3] = {1, 1, 0};
boolean SIXTEENTH[3] = {1, 1, 1};

boolean upTravelSlider = 1;
boolean upTravelWinder = 1;
double deadzone = 0.1;

// length of core, mm
int windLength = 78;
// wire gauge
int wireGauge = 25;

// mm
double wireDiameter = 8.247 * exp(-0.1159 * wireGauge);

// Slider goes 4mm every revolution, 800 steps / rotation
// Slider is kept at QUARTER speed (200 steps / mm)
// Winder is kept at EIGHTH speed (800 steps / rotation)

double stepsWinderPerSlider = 800.0 / (200.0 * wireDiameter);
double stepsWinder = 0;

long ticksSlider = 0;
long maxTicksSlider = 200 * windLength;
long revolutionCounter = 0;
long totalCounter = 0;

void setup() {
  pinMode(DIR_WINDER, OUTPUT);
  pinMode(STEP_WINDER, OUTPUT);
  pinMode(DIR_SLIDER, OUTPUT);
  pinMode(STEP_SLIDER, OUTPUT);
  digitalWrite(DIR_WINDER, HIGH);
  pinMode(SPEED_IN, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);

  pinMode(MS1_WINDER, OUTPUT);
  pinMode(MS2_WINDER, OUTPUT);
  pinMode(MS3_WINDER, OUTPUT);
  pinMode(MS1_SLIDER, OUTPUT);
  pinMode(MS2_SLIDER, OUTPUT);
  pinMode(MS3_SLIDER, OUTPUT);

  digitalWrite(MS1_WINDER, HIGH);
  digitalWrite(MS2_WINDER, HIGH);
  digitalWrite(MS3_WINDER, LOW);
  digitalWrite(MS1_SLIDER, LOW);
  digitalWrite(MS2_SLIDER, HIGH);
  digitalWrite(MS3_SLIDER, LOW);

  Serial.begin(115200);
}

double val = 0;
int timeDelay = 1000;

void loop() {
  val = ((((double) analogRead(SPEED_IN)) / 695) - 0.5) * 2; // value from -1 to 1
  if (val > 1) {
    val = 1;
  }
  else if (val < -1) {
    val = -1;
  }
  else if (abs(val) < deadzone) {
    val = 0;
  }

  timeDelay = (3000 / (abs(5 * val) + 1)) - 495;

  // SET DIRECTIONS DEPENDING ON SLIDER UP/DOWN TRAVEL
  if (val < 0) {
    if (upTravelSlider) {
      digitalWrite(DIR_SLIDER, LOW);
    }
    else {
      digitalWrite(DIR_SLIDER, HIGH);
    }
    digitalWrite(DIR_WINDER, LOW);
  }
  else {
    if (upTravelSlider) {
      digitalWrite(DIR_SLIDER, HIGH);
    }
    else {
      digitalWrite(DIR_SLIDER, LOW);
    }
    digitalWrite(DIR_WINDER, HIGH);
  }

  // STEP THE WINDER
  if (val != 0) {
    digitalWrite(STEP_WINDER, HIGH);
    delayMicroseconds(timeDelay);
    digitalWrite(STEP_WINDER, LOW);
    delayMicroseconds(timeDelay);
    if(val > 0){
      stepsWinder++;
      revolutionCounter++;
    }
    else{
      stepsWinder--;
      revolutionCounter--;
    }
    if(revolutionCounter > 800){
      totalCounter++;
      revolutionCounter = 0;
    }
    else if(revolutionCounter < 0){
      totalCounter--;
      revolutionCounter = 800;
    }
  }
  else {
    Serial.println(totalCounter);
    if ((double) analogRead(BUTTON_1) > 500) {
      if (upTravelSlider) {
        digitalWrite(DIR_SLIDER, HIGH);
        ticksSlider++;
      }
      else {
        digitalWrite(DIR_SLIDER, LOW);
        ticksSlider--;
      }
      delayMicroseconds(10);
      digitalWrite(STEP_SLIDER, HIGH);
      delayMicroseconds(1000);
      digitalWrite(STEP_SLIDER, LOW);
      delayMicroseconds(1000);
    }
    else if ((double) analogRead(BUTTON_2) > 500) {
      if (upTravelSlider) {
        digitalWrite(DIR_SLIDER, LOW);
        ticksSlider--;
      }
      else {
        digitalWrite(DIR_SLIDER, HIGH);
        ticksSlider++;
      }
      delayMicroseconds(10);
      digitalWrite(STEP_SLIDER, HIGH);
      delayMicroseconds(1000);
      digitalWrite(STEP_SLIDER, LOW);
      delayMicroseconds(1000);
    }
  }

  if (abs(stepsWinder) > stepsWinderPerSlider) {
    if (val > 0) {
      stepsWinder -= stepsWinderPerSlider;
      if (upTravelSlider) {
        ticksSlider++;
      }
      else {
        ticksSlider--;
      }
    }
    else {
      stepsWinder += stepsWinderPerSlider;
      if (upTravelSlider) {
        ticksSlider--;
      }
      else {
        ticksSlider++;
      }
    }
    digitalWrite(STEP_SLIDER, HIGH);
    delayMicroseconds(10);
    digitalWrite(STEP_SLIDER, LOW);
    delayMicroseconds(10);
  }

  // REVERSE TRAVEL DIRECTION IF NEEDED
  if (ticksSlider > maxTicksSlider) {
    upTravelSlider = !upTravelSlider;
  }
  else if (ticksSlider < 0) {
    upTravelSlider = !upTravelSlider;
  }
}
