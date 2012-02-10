#include "Arduino.h"
#include "WiFlyClient.h"
#include <WiFlySerial.h>


WiFlyClient::WiFlyClient(WiFlySerial *WiFly) {
  _WiFly = WiFly;
}

int WiFlyClient::connect(char hostname[], char path[] = "/", int port = 80) {
  _hostname = hostname;
  _port     = port;
  _path     = path;
}