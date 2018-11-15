#include "MotorWrapper.h"

MotorWrapper::MotorWrapper(int in1, int in2, int in3, int in4) : myMotor(stepsPerRevolution, in1, in2, in3, in4) {
   _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;
}

void MotorWrapper::rotate(double rotations, int speed, DIRECTION direction) {
  myMotor.setSpeed(speed * 2);
  myMotor.step((double)stepsPerRevolution * rotations * (direction == LEFT ? 1 : -1));
  disable();
}

void MotorWrapper::disable() {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
  digitalWrite(_in3, LOW);
  digitalWrite(_in4, LOW);
}
