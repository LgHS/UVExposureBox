// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "Config.h"

void HandleWebRequests();
void HandleRoot();
void HandleGetState();
void HandleGetRemainingTime();

class WebServer {
public:
	static WebServer& getInstance() {
		static WebServer instance;
		return instance;
	}
	void Update();
	void Init();

	void DoHandleWebRequests();
	void DoHandleRoot();
	void DoHandleGetState();
	void DoHandleGetRemainingTime();

	char* GetIp() {
		myIP.toString().toCharArray(ipChar, 16);
		return ipChar;
	}

private:
	char* ipChar = "xxx.xxx.xxx.xxx";
	IPAddress myIP;
	ESP8266WebServer* server = new ESP8266WebServer(WEBSERVER_PORT);
	WebServer() { }
	bool LoadFromSpiffs(String path);
};

#endif

