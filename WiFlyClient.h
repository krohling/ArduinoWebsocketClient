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
        WiFlyClient(WiFlySerial &WiFly);

        bool connect(const char *hostname, int port = 80);

        void print(const char &s);
        void print(const String &s);

        void println(const String &s);
        void println();

        int read();
        int available();

        bool connected();
        void stop();

        // debug utilities - use Serial : not NewSoftSerial as it will affect incoming stream.
        // should change these to use stream <<
        void setDebugChannel( Print* pDebug);
        Print* getDebugChannel()  { return pDebugChannel; };
        void clearDebugChannel();
        void DebugPrint( const char* pMessage);
        void DebugPrint( const int iNumber);
        void DebugPrint( const char ch);

    private:

        WiFlySerial _WiFly;
        Print* pDebugChannel;


};

#endif