#include <Stepper.h>

int forward = -1;
int backward = 1;
int directionStates[2] = {forward, backward};
int directionIndex = 0;
int stepsCompleted = 0;

const int switchPin = 2;
const float stepAngle = 1.8;
const int stepsPerRevolution = 360 / stepAngle;
bool btnPressed = false;
bool prevStatus = false;
int speed = 60; //60 RPM = 60 / 60 = 1 RPS
const int numRevolution = 5;
const int delayDuration = 500;
const int expectedSteps = stepsPerRevolution * numRevolution;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11);


int stepCount = 0; // number of steps the motor has taken

void setup() {
  // set the pushbutton as an input:
  pinMode(switchPin, INPUT);
  myStepper.setSpeed(speed);

  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (shouldItStart()) {
    // the following code is synchronous
    // myStepper.step(forward * stepsPerRevolution * numRevolution);
    // delay(delayDuration);

    // myStepper.step(backward * stepsPerRevolution * numRevolution);
    // delay(delayDuration);

    // async
    moveStep();
  }
}

bool shouldItStart() {
  int switchStatus = digitalRead(switchPin);
  if (switchStatus != prevStatus && switchStatus == HIGH) {
      btnPressed =  !btnPressed;
  }
  prevStatus = switchStatus;
  return btnPressed;
}

int getDirection() {
  if (stepsCompleted >= expectedSteps) {
    stepsCompleted = 0;
    directionIndex++;
    if(directionIndex >= sizeof(directionStates)) {
      directionIndex = 0;
    }
  }
  return directionStates[directionIndex];
}

void moveStep() {
  int direction = getDirection();
  stepsCompleted++;
  myStepper.step(direction * 1);
}


