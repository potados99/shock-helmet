#include "Motor.h"

Motor::Motor(uint8_t EN, uint8_t DIR, uint8_t CLK, uint8_t M0, uint8_t M1) {
  this->enablePin = EN;
  this->directionPin = DIR;
  this->clockPin = CLK;
  this->M0Pin = M0;
  this->M1Pin = M1;

  initPins();
  enable(false);
}

void Motor::setStepMode(uint8_t mode) {
  pinMode(this->M0Pin, OUTPUT);
  pinMode(this->M1Pin, OUTPUT);

  digitalWrite(this->M0Pin, HAS(mode, 0x02));
  digitalWrite(this->M1Pin, HAS(mode, 0x01));

  this->clocksPerStep = 0x01 << (4 - mode);
}

void Motor::setDirection(uint8_t direction) {
  digitalWrite(this->directionPin, (direction == LEFT) ? HIGH : LOW);
}

void Motor::rotate(double rotations, double speed) {
  // speed: RPM

  double rotationsPerSecond   = speed / 60L;
  double clocksPerRotation    = this->clocksPerStep * STEPS_PER_ROTAION;
  double clocksPerSecond      = rotationsPerSecond * clocksPerRotation;
  double clockCycle           = 1000L / clocksPerSecond; /* milli second */

  double totalClocks          = clocksPerStep * STEPS_PER_ROTAION * rotations; // 400

  enable(true);

  for (unsigned register int i = 0; i < totalClocks; ++ i) {
     oneClock(this->clockPin, clockCycle);
  }
  
  enable(false);
}

void Motor::initPins() {
  pinMode(this->clockPin, OUTPUT);
  pinMode(this->directionPin, OUTPUT);
  pinMode(this->enablePin, OUTPUT);
}

void Motor::enable(bool enable) {
  digitalWrite(this->enablePin, enable ? HIGH : LOW);
}

void Motor::oneClock(int pinNumber, double clockCycle) {
  digitalWrite(pinNumber, HIGH);
  delayMicroseconds(clockCycle * 500);
  digitalWrite(pinNumber, LOW);
  delayMicroseconds(clockCycle * 500);
}
