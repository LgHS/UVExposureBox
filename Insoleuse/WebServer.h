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
void HandleGetTemperature();
void HandleCancelJob();
void HandlePauseJob();
void HandleStartJob();
void HandleGetVersion();

class WebServer {
public:
	static WebServer& getInstance() {
		static WebServer instance;
		return instance;
	}
	void Update();
	void Init();
	void Stop();

	void DoHandleWebRequests();
	void DoHandleRoot();
	void DoHandleGetState();
	void DoHandleGetRemainingTime();
	void DoHandleCancelJob();
	void DoHandlePauseJob();
	void DoHandleStartJob();
	void DoHandleGetTemperature();
	void DoHandleGetVersion();

	char* GetIp() {
		myIP.toString().toCharArray(ipChar, 16);
		return ipChar;
	}

private:
	String getRemainingTimeResponse;
	String getTempResponse;

	char* ipChar = "xxx.xxx.xxx.xxx";
	IPAddress myIP;
	ESP8266WebServer* server;
	WebServer() { }
	bool LoadFromSpiffs(String path);
	void StartAP();
	void StartServer();
	bool ConnectToWiFi();
};

#endif

