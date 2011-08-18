#include <SPI.h>
#include <Ethernet.h>
#include <WebSocketClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 10 };
byte server[] = { 174, 129, 224, 73 }; //echo.websocket.org

WebSocketClient client(server, "/", 80);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  
  if(client.connect()) {
    client.setDataArrivedDelegate(dataArrived);
  }
  else {
    while(1) {}
  }
}

boolean sent = false;

void loop() {
  client.monitor();
  
  if(!sent) {
    client.send("Hello World!");
    sent = true;
  }
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
