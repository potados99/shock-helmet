#include "SerialWrapper.h"

void SerialWrapper::triggerCallback() {
  if (! this->callbackRegistered) return; // exception
  if (this->byteIndex == 0) return; // nothing recieved

  this->onRecieved(this->recievedBytes);
}

void SerialWrapper::clearBuffer() {
  memset(this->recievedBytes, 0, RECIEVE_BUFFER_SIZE);
  byteIndex = 0;
}

void SerialWrapper::appendToBuffer(byte b) {
  if (this->byteIndex >= RECIEVE_BUFFER_SIZE - 1) return; // exception

  this->recievedBytes[this->byteIndex ++] = b;
}


SerialWrapper::SerialWrapper() {
  clearBuffer();
}


void SerialWrapper::registerSerial(HardwareSerial *serial) {
  if (serial != nullptr) {
    this->serial = serial;
    this->serialRegistered = true;

    this->serial->begin(9600);
  }
}

void SerialWrapper::registerCallback(byte terminate, callback cb) {
  if (cb != nullptr) {
    this->onRecieved = cb;
    this->callbackRegistered = true;
  }
}

void SerialWrapper::loop() {
  if (! this->serialRegistered) return; //exception
  if (! this->callbackRegistered) return;

  if (! this->serial->available()) return;

  byte recieved = this->serial->read();

  if (recieved == this->terminate) {
    triggerCallback();
    clearBuffer();
    return;
  }

  appendToBuffer(recieved);
}
