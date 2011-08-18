#include <WiFly.h>
#include <WebSocketClient.h>

WebSocketClient client("echo.websocket.org", "/", 80);

void setup() {
  Serial.begin(9600);
  WiFly.begin();
  if (!WiFly.join("Your-Network", "YourPassword")) {
  	Serial.println("Not Connected To The Network");
     while(1) {}
  }
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
