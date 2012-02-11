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

        bool connect(const char hostname[], int port = 80);

        void print(const char &s);
        void print(const String &s);

        void println(const String &s);
        void println();

        int read();
        int available();

        bool connected();
        void stop();

    private:

        WiFlySerial _WiFly;

};

#endif