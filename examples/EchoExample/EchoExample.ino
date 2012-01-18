#include "Arduino.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>

boolean sent = false;
byte mac[] = {  0x00, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "echo.websocket.org";
WebSocketClient client;

void setup() {
  Serial.begin(9600);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Init Ethernet failed");
    for(;;)
      ;
  }
  
  Serial.println("Connecting...");
  if(client.connect(server)) {
    Serial.println("Connected");
    client.setDataArrivedDelegate(dataArrived);
  }
  else {
    Serial.println("Not Connected");
  }
}

void loop() {
  if(client.connected()) {
    client.monitor();
    
    if(!sent) {
      client.send("Hello World!");
      Serial.println("Sent: Hello World!");
      sent = true;
    }
  }
  else {
    Serial.println("Not Connected");
  }
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}

