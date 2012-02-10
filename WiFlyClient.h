#ifndef WIFLYCLIENT_H
#define WIFLYCLIENT_H

#include "Arduino.h"

#include <WiFlySerial.h>
#include <SoftwareSerial.h>
#include <Streaming.h>

class WiFlyClient {

public:

  // constructor expects an initialized, and fully
  // connected instance of the WiFly driver.
  // Let the user worry about authentication and pin mapping.
  WiFlyClient(WiFlySerial *WiFly);

  bool connect(char hostname[], char path[] = "/", int port = 80);

  void print(const char *str);
  void print(const String *str);

  void println(const String *str);

  int read();
  int available();

  bool connected();
  void stop();

private:

  WiFlySerial _WiFly;
  int _port;
  char _hostname[];

};

#endif