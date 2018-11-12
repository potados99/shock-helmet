#include "Motor.h"
#include "SerialWrapper.h"

Motor myMotor(3, 4, 2, 5, 6);
// enable, direction, clock, m0, m1

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
  Serial.println(data[0]);

  myMotor.setDirection(LEFT);
  myMotor.rotate(0.1, 20);
  myMotor.setDirection(RIGHT);
  myMotor.rotate(0.1, 20);

}
