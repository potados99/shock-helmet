#ifndef _SERIAL_WRAPPER
#define _SERIAL_WRAPPER

#include "Arduino.h"

#define RECIEVE_BUFFER_SIZE 8

typedef void (*callback)(String);

/**
 * 아두이노의 HardwareSerial 클래스와 콜백을 사용한 시리얼 통신 클래스입니다.
 */
class SerialWrapper {
private:
  HardwareSerial  *serial;

  /* 도착한 바이트들을 이어붙여 저장하는 문자열. */
  String          receivedString;

  /* 막 도착한 문자 바이트. */
  char            incomming;

  /* 이 문자가 도착하면 데이터가 끝난 것으로 간주하고 콜백을 실행. */
  char            terminate;

  /* 콜백을 실행할 조건이 갖추어졌는지 확인하는 플래그. */
  bool            serialRegistered = false;
  bool            callbackRegistered = false;

  /* 데이터가 도착했을 때 실행할 콜백. */
  callback        onReceived;

  /* 콜백을 안전하게 실행. */
  void            triggerCallback();

  /* receivedString을 초기화. */
  void            clearBuffer();

  /**
   * receivedString에 바이트 추가.
   * @param b           추가할 문자 바이트.
   */
  void            appendToBuffer(char b);

public:
  SerialWrapper();

  /**
   * HardwareSerial   객체를 등록.
   * @param serial    등록할 시리얼 객체.
   */
  void            registerSerial(HardwareSerial *serial);

  /**
   * 콜백을 등록.
   * @param terminate   데이터의 끝을 알리는 문자.
   * @param cb          등록할 콜백.
   */
  void            registerCallback(char terminate, callback cb);

  /* 호출될 때 마다 작업을 수행. loop()에서 반드시 호출해주어야 함. */
  void            loop();
};

#endif
