// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "Config.h"

void HandleWebRequests();
void HandleRoot();

class WebServer {
public:
	static WebServer& getInstance() {
		static WebServer instance;
		return instance;
	}
	IPAddress MyIP;
	void Update();
	void Init();
	bool LoadFromSpiffs(String path);
	   
	ESP8266WebServer* server = new ESP8266WebServer(WEBSERVER_PORT);
private:
	WebServer() { }
};

#endif

