#include "Motor.h"

Motor myMotor(2);

void setup() {

}

void loop() {
  // default 16th step mode, right direction.
  // for clock controled step motor driver.
  myMotor.rotate(2, 200);
}
