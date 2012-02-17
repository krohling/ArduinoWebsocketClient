#include "Arduino.h"
#include <WebSocketClient.h>
#include <WiFlySerial.h>
#include <SoftwareSerial.h>
#include <Streaming.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "echo.websocket.org";
WebSocketClient client(2, 3, "2WIRE598", "8888986907");

void setup() {
  Serial.begin(9600);
  client.setDebugChannel( (Print*) &Serial);
  client.connect(server);
  client.setDataArrivedDelegate(dataArrived);
  client.send("Hello World!");
  Serial.println("here");
}

void loop() {
  client.monitor();
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
