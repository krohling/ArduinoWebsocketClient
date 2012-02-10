#include "Arduino.h"
#include "WiFlyClient.h"
#include <WiFlySerial.h>

WiFlyClient::WiFlyClient(WiFlySerial *WiFly) {
  _WiFly = WiFly;
}

bool WiFlyClient::connect(char hostname[], int port = 80) {
  _hostname = hostname;
  _port     = port;
  return _WiFly.openConnection(hostname, port);
}

void print(const char *str) {
  _WiFly.uart.print(str);
}

void print(const String *str) {
  _WiFly.uart.print(str);
}

void println(const String *str) {
  _WiFly.uart.println(str);
}

int read() {
  return _WiFly.uart.read();
}

int available() {
  return _WiFly.uart.available();
}

bool connected() {
  return _WiFly.isConnected();
}

void stop() {
  _WiFly.closeConnection();
}