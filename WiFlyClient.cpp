#include "WiFlyClient.h"
#include <WiFlySerial.h>

#define ARD_DEFAULT_RX_PIN 2
#define ARD_DEFAULT_TX_PIN 3

WiFlyClient::WiFlyClient(int rxPin, int txPin, const char *ssid, const char *password) : _WiFly(rxPin, txPin) {
    initializeWiFly(ssid, password);
}

WiFlyClient::WiFlyClient(const char *ssid, const char *password) : _WiFly(ARD_DEFAULT_RX_PIN, ARD_DEFAULT_TX_PIN) {
    initializeWiFly(ssid, password);
}

WiFlyClient::WiFlyClient(WiFlySerial &WiFly) : _WiFly(WiFly) {

}


void WiFlyClient::initializeWiFly(const char *ssid, const char *password) {
    _WiFly.begin();
    if (!_WiFly.isConnected()) {
        _WiFly.leave(); // restart my link
        _WiFly.SendCommand("set com remote 0", "AOK");
        _WiFly.SendCommand("set opt jointmr 5000", "AOK");
        _WiFly.setSSID(ssid);
        _WiFly.setPassphrase(password);
        _WiFly.join();
    }
}

bool WiFlyClient::connect(const char *hostname, int port) {
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

// implementation thanks to Tom Waldock and his
// his WiFlySerial project.

// setDebugChannel
// Conduit for debug output
// must not be a NewSoftSerial instance as incoming interrupts conflicts with outgoing data.
void WiFlyClient::setDebugChannel(Print* pChannel) {
    pDebugChannel = pChannel;
}
void WiFlyClient::clearDebugChannel() {
    pDebugChannel = NULL;
}

void WiFlyClient::DebugPrint(const char* pMessage) {
    if ( pDebugChannel )
        pDebugChannel->println(pMessage);
}
void WiFlyClient::DebugPrint(const int iNumber) {
    if ( pDebugChannel )
        pDebugChannel->println(iNumber);
}
void WiFlyClient::DebugPrint(const char ch) {
  if ( pDebugChannel )
    pDebugChannel->print(ch);
}

