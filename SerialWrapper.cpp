#include "SerialWrapper.h"

void SerialWrapper::triggerCallback() {
  if (! this->callbackRegistered) return; // exception

  this->onRecieved(this->receivedString);
}

void SerialWrapper::clearBuffer() {
  this->receivedString = "";
}

void SerialWrapper::appendToBuffer(char b) {
  this->receivedString += b;
  Serial.println(this->receivedString);
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

void SerialWrapper::registerCallback(char terminate, callback cb) {
  if (cb != nullptr) {
    this->onReceived = cb;
    this->callbackRegistered = true;
  }

  this->terminate = terminate;
}

void SerialWrapper::loop() {
  if (! this->serialRegistered) return; //exception
  if (! this->callbackRegistered) return;

  if (! this->serial->available()) return;

  char recieved = this->serial->read();

  if (recieved == this->terminate) {
    triggerCallback();
    clearBuffer();
    return;
  }

  appendToBuffer(recieved);
}
