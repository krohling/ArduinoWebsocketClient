/*
 WebsocketClient, a websocket client for Arduino
 Copyright 2011 Kevin Rohling
 http://kevinrohling.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <WebSocketClient.h>
#include <WString.h>
#include <string.h>
#include <stdlib.h>

prog_char stringVar[] PROGMEM = "{0}";
prog_char clientHandshakeLine1[] PROGMEM = "GET {0} HTTP/1.1";
prog_char clientHandshakeLine2[] PROGMEM = "Upgrade: WebSocket";
prog_char clientHandshakeLine3[] PROGMEM = "Connection: Upgrade";
prog_char clientHandshakeLine4[] PROGMEM = "Host: {0}";
prog_char clientHandshakeLine5[] PROGMEM = "Origin: ArduinoWebSocketClient";
prog_char serverHandshake[] PROGMEM = "HTTP/1.1 101";

PROGMEM const char *WebSocketClientStringTable[] =
{   
    stringVar,
    clientHandshakeLine1,
    clientHandshakeLine2,
    clientHandshakeLine3,
    clientHandshakeLine4,
    clientHandshakeLine5,
    serverHandshake
};

String WebSocketClient::getStringTableItem(int index) {
    char buffer[35];
    strcpy_P(buffer, (char*)pgm_read_word(&(WebSocketClientStringTable[index])));
    return String(buffer);
}

bool WebSocketClient::connect(char hostname[], char path[], int port) {
    bool result = false;

    if (_client.connect(hostname, port)) {
        sendHandshake(hostname, path);
        result = readHandshake();
    }
    
	return result;
}


bool WebSocketClient::connected() {
    return _client.connected();
}

void WebSocketClient::disconnect() {
    _client.stop();
}

void WebSocketClient::monitor () {
    char character;
    
	if (_client.available() > 0 && (character = _client.read()) == 0) {
        String data = "";
        bool endReached = false;
        while (!endReached) {
            character = _client.read();
            endReached = character == -1;

            if (!endReached) {
                data += character;
            }
        }
        
        if (_dataArrivedDelegate != NULL) {
            _dataArrivedDelegate(*this, data);
        }
    }
}

void WebSocketClient::setDataArrivedDelegate(DataArrivedDelegate dataArrivedDelegate) {
	  _dataArrivedDelegate = dataArrivedDelegate;
}


void WebSocketClient::sendHandshake(char hostname[], char path[]) {
    String stringVar = getStringTableItem(0);
    String line1 = getStringTableItem(1);
    String line2 = getStringTableItem(2);
    String line3 = getStringTableItem(3);
    String line4 = getStringTableItem(4);
    String line5 = getStringTableItem(5);
    
    line1.replace(stringVar, path);
    line4.replace(stringVar, hostname);
    
    _client.println(line1);
    _client.println(line2);
    _client.println(line3);
    _client.println(line4);
    _client.println(line5);
    _client.println();
}

bool WebSocketClient::readHandshake() {
    bool result = false;
    char character;
    String handshake = "", line;
    int maxAttempts = 300, attempts = 0;
    
    while(_client.available() == 0 && attempts < maxAttempts) 
    { 
        delay(100); 
        attempts++;
    }
    
    while((line = readLine()) != "") {
        handshake += line + '\n';
    }
    
    String response = getStringTableItem(6);
    result = handshake.indexOf(response) != -1;
    
    if(!result) {
        _client.stop();
    }
    
    return result;
}

String WebSocketClient::readLine() {
    String line = "";
    char character;
    
    while(_client.available() > 0 && (character = _client.read()) != '\n') {
        if (character != '\r' && character != -1) {
            line += character;
        }
    }
    
    return line;
}

void WebSocketClient::send (String data) {
    _client.print((char)0);
	_client.print(data);
    _client.print((char)255);
}

