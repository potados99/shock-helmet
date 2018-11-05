#include "Motor.h"

Motor myMotor(3, 4, 2, 5, 6);
// enable, direction, clock, m0, m1

void setup() {
  myMotor.setDirection(LEFT);
  myMotor.setStepMode(HALF_STEP); // fast and unstable
}

void loop() {
  // default 16th step mode, right direction.
  myMotor.rotate(0.3, 200);
  myMotor.setDirection(RIGHT);
  myMotor.rotate(0.3, 200);
  myMotor.setDirection(LEFT);

  myMotor.rotate(0.3, 200);
  myMotor.setDirection(RIGHT);
  myMotor.rotate(0.3, 200);
  myMotor.setDirection(LEFT);


  delay(150);
}
