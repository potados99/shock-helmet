#include "SerialWrapper.h"
#include "MotorWrapper.h"

MotorWrapper myMotor(2, 3, 4, 5);
SerialWrapper serialWrapper;

// 시리얼 포트로 데이터가 도착했을 때 실행할 콜백함수(이하 '콜백')의 원형입니다.
void dataRecieved(String data);

// 제일 처음에 실행됩니다.
void setup() {
  serialWrapper.registerSerial(&Serial);
  serialWrapper.registerCallback('\n', dataRecieved);
}

// setup 이후 무한 반복됩니다.
void loop() {
//  myMotor.setDirection(LEFT);
//  myMotor.rotate(0.8, 200);
//  myMotor.setDirection(RIGHT);
//  myMotor.rotate(0.8, 200);

  serialWrapper.loop();
}

// 콜백의 정의입니다.
void dataRecieved(String data) {
  // 데이터는 16진수를 나타내는 문자열로 이루어져 있습니다.
  // 데이터의 포맷은 다음과 같습니다:
  // AABBCCDD
  //
  // 여기서,
  // AA는 회전 수를,
  // BB는 회전 속도를 (0부터 255까지.),
  // CC는 회전 사이 지연 시간을 (밀리세컨드 단위.),
  // DD는 한 번 회전에 돌아갈 각도를 나타냅니다 (0부터 100까지.).

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
