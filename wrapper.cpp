#include "SerialWrapper.h"
#include "MotorWrapper.h"

MotorWrapper myMotor(2, 3, 4, 5);
SerialWrapper serialWrapper;

void dataRecieved(String data);

void setup() {
  serialWrapper.registerSerial(&Serial);
  serialWrapper.registerCallback('\n', dataRecieved);
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
  uint8_t _delay = (uint8_t)strtol(data.substring(4, 6).c_str(), 0, 16);
  uint8_t angle = (uint8_t)strtol(data.substring(6, 8).c_str(), 0, 16);

  static uint8_t direction = LEFT;

  for (uint8_t i = 0; i < times; ++ i) {
    myMotor.rotate((double)angle / 100, speed, direction);

    if (direction == LEFT) direction = RIGHT;
    else if (direction == RIGHT) direction = LEFT;

    delay(_delay);
  }
}
