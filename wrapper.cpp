#include "Motor.h"

Motor myMotor(3, 4, 2, 5, 6);
// enable, direction, clock, m0, m1

void setup() {
  myMotor.setDirection(LEFT);
  myMotor.setStepMode(HALF_STEP); // fast and unstable
  myMotor.rotate(0.8, 300);
  myMotor.setDirection(RIGHT);
  myMotor.rotate(0.8, 300);

}

void loop() {

//  myMotor.setDirection(LEFT);
//  myMotor.rotate(0.8, 200);
//  myMotor.setDirection(RIGHT);
//  myMotor.rotate(0.8, 200);

  delay(150);
}
