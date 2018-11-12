#include "Motor.h"
#include "SerialWrapper.h"

Motor myMotor(3, 4, 2, 5, 6);
// enable, direction, clock, m0, m1

SerialWrapper serialWrapper;

void dataRecieved(String data);

void setup() {
  serialWrapper.registerSerial(&Serial);
  serialWrapper.registerCallback('\n', dataRecieved);
  myMotor.setStepMode(SIXTEENTH_STEP);
  myMotor.rotate(1, 60);

}

void loop() {

//  myMotor.setDirection(LEFT);
//  myMotor.rotate(0.8, 200);
//  myMotor.setDirection(RIGHT);
//  myMotor.rotate(0.8, 200);

  serialWrapper.loop();
}

void dataRecieved(String data) {
  uint8_t times = (uint8_t)strtol(data.substring(0, 2).c_str(), 0, 16);
  uint8_t speed = (uint8_t)strtol(data.substring(2, 4).c_str(), 0, 16);

  static uint8_t direction;

  for (uint8_t i = 0; i < times; ++ i) {
    if (direction == LEFT) direction = RIGHT;
    else if (direction == RIGHT) direction = LEFT;

    myMotor.setDirection(direction);
    myMotor.rotate(0.7, speed * 1.5);
  }
}
