#include "WiFlyClient.h"
#include <WiFlySerial.h>

WiFlyClient::WiFlyClient(WiFlySerial &WiFly) : _WiFly(WiFly) {

}

bool WiFlyClient::connect(const char hostname[], int port) {
    return _WiFly.openConnection(hostname, port);
}

void WiFlyClient::print(const char &s) {
    _WiFly.uart.print(s);
}

void WiFlyClient::print(const String &s) {
    _WiFly.uart.print(s);
}

void WiFlyClient::println(const String &s) {
    _WiFly.uart.println(s);
}

void WiFlyClient::println() {
    _WiFly.uart.println("\n");
}

int WiFlyClient::read() {
    return _WiFly.uart.read();
}

int WiFlyClient::available() {
    return _WiFly.uart.available();
}

bool WiFlyClient::connected() {
    return _WiFly.isConnected();
}

void WiFlyClient::stop() {
    _WiFly.closeConnection();
}