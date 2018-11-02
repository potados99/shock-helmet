#ifndef _Motor_h
#define _Motor_h

#include "Arduino.h"

#define HAS(X, Y) ((X) & (Y))

#define ENABLE_PIN_NUMBER 2
#define M0_PIM_NUMBER 3
#define M1_PIM_NUMBER 4
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
  uint8_t pin;
  uint8_t direction = RIGHT;
  uint16_t clocksPerStep = 0x02;

  void initPins();
  void enable(bool enable);

  void oneClock(int pinNumber, double clockCycle);

public:
  Motor(int pin);

  void setStepMode(Mode mode);
  void setDirection(uint8_t direction);

  void rotate(double rotations, double speed);
};


#endif
