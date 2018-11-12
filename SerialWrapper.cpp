#include "SerialWrapper.h"

void SerialWrapper::triggerCallback() {
  if (! this->callbackRegistered) return; // exception

  this->onRecieved(this->recievedString);
}

void SerialWrapper::clearBuffer() {
  this->recievedString = "";
}

void SerialWrapper::appendToBuffer(char b) {
  this->recievedString += b;
  Serial.println(this->recievedString);
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
    this->onRecieved = cb;
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
