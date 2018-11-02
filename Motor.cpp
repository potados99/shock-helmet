#include "Motor.h"

Motor::Motor(int pin);

void Motor::setStepMode(Mode mode) {
  pinMode(MODE0_PIM_NUMBER, OUTPUT);
  pinMode(MODE1_PIM_NUMBER, OUTPUT);

  digitalWrite(MODE0_PIM_NUMBER, HAS(mode & 0x02));
  digitalWrite(MODE1_PIM_NUMBER, HAS(mode & 0x01));

  this->clocksPerStep = 0x01 << (4 - _mode);
}

void Motor::setDirection(uint8_t direction) {
  digitalWrite(this->pin, (direction == LEFT) ? HIGH : LOW);
}

void Motor::rotate(double rotations, double speed) {
  // speed: RPM

  double rotationsPerSecond   = speed / 60L;
  double clocksPerRotation    = this->clocksPerStep * STEPS_PER_ROTAION;
  double clocksPerSecond      = rotationsPerSecond * clocksPerRotation;
  double clockCycle           = 1000L / clocksPerSecond; /* milli second */

  double totalClocks          = clocksPerStep * STEPS_PER_ROTAION * rotations; // 400

  for (unsigned register int i = 0; i < totalClocks; ++ i) {
     oneClock(CLOCK_PIN_NUMBER, clockCycle);
  }
}

void Motor::initPins() {
  pinMode(CLOCK_PIN_NUMBER, OUTPUT);
  pinMode(DIRECTION_PIN_NUMBER, OUTPUT);
  pinMode(ENABLE_PIN_NUMBER, OUTPUT);
}

void Motor::enable(bool enable) {
  digitalWrite(ENABLE_PIN_NUMBER, enable ? HIGH : LOW);
}

void Motor::oneClock(int pinNumber, double clockCycle) {
  digitalWrite(pinNumber, HIGH);
  delayMicroseconds(clockCycle * 500);
  digitalWrite(pinNumber, LOW);
  delayMicroseconds(clockCycle * 500);
}
