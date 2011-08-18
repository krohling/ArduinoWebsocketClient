#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H_

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include <Client.h>
#include "WProgram.h"

//Uncomment this to use WIFLY Client
//#define WIFLY true

class WebSocketClient {
	public:
#ifdef WIFLY
		WebSocketClient(const char *hostname, String path, int port = 80);
#else
        WebSocketClient(byte server[], String path, int port = 80);
#endif
		typedef void (*DataArrivedDelegate)(WebSocketClient client, String data);
		bool connect();
        bool connected();
        void disconnect();
		void monitor();
		void setDataArrivedDelegate(DataArrivedDelegate dataArrivedDelegate);
		void send(String data);
        void sendHandshake();
	private:
		Client _client;
        int _port;
        String _path;
        String _hostname;
        DataArrivedDelegate _dataArrivedDelegate;
        bool readHandshake();
        String readLine();
};


#endif
