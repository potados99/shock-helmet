#ifndef _MOTOR_WRAPPER_H
#define _MOTOR_WRAPPER_H

#include "Arduino.h"
#include <Stepper.h>

typedef enum _DIRECTION {
  RIGHT = 0, // default
  LEFT = 1
} DIRECTION;

class MotorWrapper {
private:
  Stepper myMotor;

  static const int stepsPerRevolution = 200;
  int _in1;
  int _in2;
  int _in3;
  int _in4;

  void disable();

public:
  MotorWrapper(int in1, int in2, int in3, int in4);

  void rotate(double rotations, int speed, DIRECTION direction);
};




#endif
