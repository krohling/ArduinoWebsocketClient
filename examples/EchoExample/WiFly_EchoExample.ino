#include "Arduino.h"
#include <WebSocketClient.h>
#include <WiFlySerial.h>
#include <SoftwareSerial.h>
#include <Streaming.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "echo.websocket.org";
WebSocketClient client("ssid", "password");

void setup() {
  Serial.begin(9600);
  client.connect(server);
  client.setDataArrivedDelegate(dataArrived);
  client.send("Hello World!");
}

void loop() {
  client.monitor();
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
