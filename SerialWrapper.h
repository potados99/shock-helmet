#ifndef _SERIAL_WRAPPER
#define _SERIAL_WRAPPER

#include "Arduino.h"

#define RECIEVE_BUFFER_SIZE 8

typedef void (*callback)(String);

class SerialWrapper {
private:
  HardwareSerial  *serial;

  String          recievedString;
  char            incomming;
  char            terminate;

  bool            serialRegistered = false;
  bool            callbackRegistered = false;

  callback        onRecieved;
  void            triggerCallback();

  void            clearBuffer();
  void            appendToBuffer(char b);

public:
  SerialWrapper();

  void            registerSerial(HardwareSerial *serial);
  void            registerCallback(char terminate, callback cb);
  void            loop();
};

#endif
