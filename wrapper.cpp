#include "Motor.h"

Motor myMotor(3, 4, 2, 5, 6);

void setup() {
  myMotor.setDirection(LEFT);
  myMotor.setStepMode(HALF_STEP);
}

void loop() {
  // default 16th step mode, right direction.
  // for clock controled step motor driver.
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
