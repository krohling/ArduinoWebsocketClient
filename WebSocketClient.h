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

#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H_

//Uncomment this to use WIFLY Client
#define WIFLY true

#include <string.h>
#include <stdlib.h>
#include <WString.h>


#ifdef WIFLY
#include "WiFlyClient.h"
#include <WiFlySerial.h>
#else
#include <Ethernet.h>
#endif

#include "Arduino.h"

class WebSocketClient {

    public:

#ifdef WIFLY
        WebSocketClient(WiFlySerial &WiFly);
#else
        WebSocketClient();
#endif

        typedef void (*DataArrivedDelegate)(WebSocketClient client, String data);
        bool connect(const char *hostname, const char *path = "/", int port = 80);
        bool connected();
        void disconnect();
        void monitor();
        void setDataArrivedDelegate(DataArrivedDelegate dataArrivedDelegate);
        void send(String data);

        // debug utilities - use Serial : not NewSoftSerial as it will affect incoming stream.
        // should change these to use stream <<
        void setDebugChannel( Print* pDebug);
        Print* getDebugChannel()  { return pDebugChannel; };
        void clearDebugChannel();
        void DebugPrint( const char* pMessage);
        void DebugPrint( const int iNumber);
        void DebugPrint( const char ch);


    private:

        String getStringTableItem(int index);
        void sendHandshake(const char *hostname, const char *path);
        Print* pDebugChannel;


#ifndef WIFLY
        EthernetClient _client;
#else
        WiFlyClient _client;
#endif

        DataArrivedDelegate _dataArrivedDelegate;
        bool readHandshake();
        String readLine();
};


#endif
