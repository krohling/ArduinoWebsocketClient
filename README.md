# ArduinoWebsocketClient, an Arduino client for connecting and messaging with Websockets

Websockets currently provide a simple and lightweight way to send and receive messages from web browsers.  This project was developed to extend this capability to embedded devices (Arduinos).  It is my hope that allowing devices to easily send information about themselves as well as respond to messages received from hosted services will result in some interesting applications.

## Caveats

This library doesn't support every inch of the Websocket spec, most notably the use of a Sec-Websocket-Key.  Also, because Arduino doesn't support SSL, this library also doesn't support the use of Websockets over https.  If you're interested in learning more about the Websocket spec I recommend checking out the [Wikipedia Page](http://en.wikipedia.org/wiki/WebSocket).  Now that I've got that out of the way, I've been able to successfully use this to connect to several hosted Websocket services, including: [echo.websocket.org](http://websocket.org/echo.html) and [pusherapp.com](http://pusherapp.com).

## Installation instructions

Once you've clone this repo locally, copy the ArduinoWebsocketClient directory into your Arduino Sketchbook directory under Libraries then restart the Arduino IDE so that it notices the new library.  Now, under File\Examples you should see ArduinoWebsocketClient.  To use the library in your app, select Sketch\Import Library\ArduinoWebsocketClient.

## How To Use This Library

```
byte server[] = { 174, 129, 224, 73 }; //echo.websocket.org
WebSocketClient client(server, "/", 80);

void setup() {
  Ethernet.begin(mac, ip);
  client.connect();
  client.setDataArrivedDelegate(dataArrived);
  client.send("Hello World!");
}

void loop() {
  client.monitor();
}

void dataArrived(WebSocketClient client, String data) {
  Serial.println("Data Arrived: " + data);
}
```

## Examples

There are two examples included with this library.  The first, EchoExample will connect to echo.websocket.org, which hosts a service that simply echos any messages that you send it via Websocket.  This example sends the message "Hello World!".  If the example runs correctly, the Arduino will receive this same message back over the Websocket and print it via Serial.println.  The second example does the exact same thing, but is modified to work with the [WiFly Client library](https://github.com/sparkfun/WiFly-Shield).  For this example to compile correctly you must open WebsocketClient.h and follow instructions to uncomment the specified compiler directive.  If your Arduino uses an Ethernet shield don't bother with the WiFly example.