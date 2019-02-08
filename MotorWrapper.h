#ifndef _MOTOR_WRAPPER_H
#define _MOTOR_WRAPPER_H

#include "Arduino.h"
#include <Stepper.h>

typedef enum _DIRECTION {
  RIGHT = 0, // default
  LEFT = 1
} DIRECTION;

/**
 * 스텝모터를 간단히 제어할 수 있게 도와주는 클래스입니다.
 * 아두이노의 Stepper 클래스를 사용합니다.
 */
class MotorWrapper {
private:
  /* Stepper 객체. */
  Stepper myMotor;

  /* 한 바퀴당 스텝 수. 모터마다 다릅니다. */
  static const int stepsPerRevolution = 200;

  /**
   * 모터 구동에 사용할 GPIO 핀.
   * 2상 4선 바이폴라 기준 4개 핀이 사용됩니다.
   */
  int _in1;
  int _in2;
  int _in3;
  int _in4;

  /* 모터로 향하는 출력을 끕니다. */
  void disable();

public:
  MotorWrapper(int in1, int in2, int in3, int in4);

  /**
   * 모터를 회전시킵니다.
   * @param rotations     회전할 바퀴 수입니다.
   * @param speed         회전할 속도입니다.
   * @param direction     회전할 방향입니다.
   */
  void rotate(double rotations, int speed, DIRECTION direction);
};




#endif
