#include "Motor.h"
#include "SerialWrapper.h"

Motor myMotor(3, 4, 2, 5, 6);
// enable, direction, clock, m0, m1

SerialWrapper serialWrapper;

void dataRecieved(byte *data);

void setup() {
  serialWrapper.registerSerial(&Serial);
  serialWrapper.registerCallback(0xFF, dataRecieved);
}

void loop() {

//  myMotor.setDirection(LEFT);
//  myMotor.rotate(0.8, 200);
//  myMotor.setDirection(RIGHT);
//  myMotor.rotate(0.8, 200);

  serialWrapper.loop();
}

void dataRecieved(byte *data) {
  Serial.println((uint8_t)data[0]);

  for (uint8_t i = 0; i < data[0]; ++ i) {
    myMotor.setDirection(LEFT);
    myMotor.rotate(0.1, 20);
    myMotor.setDirection(RIGHT);
    myMotor.rotate(0.1, 20);
  }


}
