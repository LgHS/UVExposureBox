// WebServer.h

#ifndef _WEBSERVER_h
#define _WEBSERVER_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

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
	   
	ESP8266WebServer* server = new ESP8266WebServer(80);
private:

	const char* imagefile = "/image.png";
	const char* htmlfile = "/index.html";

	const char *ssid = "image-demo-circuits4you.com";
	const char *password = "password";

	WebServer() { }
};

#endif

