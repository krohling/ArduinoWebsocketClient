#include <WebSocketClient.h>
#include <WString.h>
#include <string.h>
#include <stdlib.h>
#include "WProgram.h"

#ifdef WIFLY
WebSocketClient::WebSocketClient(const char *hostname, String path, int port) :
	_client(hostname, port)
{
    _port = port;
    _hostname = hostname;
    _path = path;
}
#else
WebSocketClient::WebSocketClient(byte server[], String path, int port) :
    _client(server, port)
{
    _port = port;
    _path = path;
    
    _hostname = String();
    int size = sizeof(server);
    for (int i = 0; i < size; i++) {
        _hostname += String(server[i]);
        
        if (i != size-1) {
            _hostname += ".";
        }
    }
    
}
#endif

bool WebSocketClient::connect() {
    bool result = false;
    if (_client.connect()) {
        sendHandshake();
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
	if ((character = _client.read()) == 0) {
        String data = "";
        bool done = false;
        bool endReached = false;
        while (!done) {
            character = _client.read();
            if (character != -1) {
                data += character;
                endReached = false;
            }
            else if(endReached) {
                done = true;
            }
            else {
                endReached = true;
                delay(10);
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

bool WebSocketClient::readHandshake() {
    bool result = false;
    char character;
    String handshake = "", line;
    
    while((character = _client.read()) == -1) {}
    handshake += character;
    
    while((line = readLine()) != "") {
        handshake += line;
    }
    
    result = handshake.indexOf("HTTP/1.1 101 Web Socket Protocol Handshake") != -1;
    
    return result;
}

void WebSocketClient::sendHandshake() {
    _client.print("GET ");
    _client.print(_path);
    _client.println(" HTTP/1.1");
    _client.println("Upgrade: WebSocket");
    _client.println("Connection: Upgrade");
    _client.print("Host: ");
    _client.print(_hostname);
    _client.print(":");
    _client.println(_port);
    _client.println("Origin: ArduinoWebSocketClient");
    _client.println();
}

String WebSocketClient::readLine() {
    String line = "";
    char character;
    while((character = _client.read()) != '\n') {
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

