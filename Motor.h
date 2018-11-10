#ifndef _MOTOR_H
#define _MOTOR_H

#include "Arduino.h"

#define HAS(X, Y) ((X) & (Y))

#define ENABLE_PIN_NUMBER 2
#define M0_PIN_NUMBER 3
#define M1_PIN_NUMBER 4
#define CLOCK_PIN_NUMBER 8
#define DIRECTION_PIN_NUMBER 9

#define STEP_ANGLE (1.8L)
#define STEPS_PER_ROTAION (360L / STEP_ANGLE) /* One Step */
#define MAX_SPEED 2100

typedef enum _STEP_MODE {
  SIXTEENTH_STEP = 0, // default
  EIGHTH_STEP = 1,
  QUARTER_STEP = 2,
  HALF_STEP = 3
} STEP_MODE;

typedef enum _DIRECTION {
  RIGHT = 0, // default
  LEFT = 1
} DIRECTION;

class Motor {
private:
  uint8_t enablePin;
  uint8_t directionPin;
  uint8_t clockPin;
  uint8_t M0Pin;
  uint8_t M1Pin;

  uint8_t direction = RIGHT;
  uint16_t clocksPerStep = 0x02;

  void initPins();
  void enable(bool enable);

  void oneClock(int pinNumber, double clockCycle);

public:
  Motor(uint8_t EN, uint8_t DIR, uint8_t CLK, uint8_t M0, uint8_t M1);

  void setStepMode(uint8_t mode);
  void setDirection(uint8_t direction);

  void rotate(double rotations, double speed);
};


#endif
