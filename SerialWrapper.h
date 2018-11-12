#ifndef _SERIAL_WRAPPER
#define _SERIAL_WRAPPER

#include "Arduino.h"

#define RECIEVE_BUFFER_SIZE 8

typedef void (*callback)(byte*);

class SerialWrapper {
private:
  HardwareSerial  *serial;

  byte            recievedBytes[RECIEVE_BUFFER_SIZE];
  uint8_t         byteIndex = 0;
  byte            incommingByte;
  char            terminate;

  bool            serialRegistered = false;
  bool            callbackRegistered = false;

  callback        onRecieved;
  void            triggerCallback();

  void            clearBuffer();
  void            appendToBuffer(byte b);

public:
  SerialWrapper();

  void            registerSerial(HardwareSerial *serial);
  void            registerCallback(byte terminate, callback cb);
  void            loop();
};

#endif
