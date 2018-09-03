// 
// 
// 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "Config.h"
#include "WebServer.h"

void WebServer::Init() {
	SPIFFS.begin();

	WiFi.mode(WIFI_AP);
	uint8_t mac[WL_MAC_ADDR_LENGTH];
	WiFi.softAPmacAddress(mac);
	WiFi.softAP(WEBSERVER_SSID, WEBSERVER_PWD);
	this->MyIP = WiFi.softAPIP();

	this->server->on("/", HandleRoot);
	this->server->onNotFound(HandleWebRequests);
	this->server->begin();
}

void WebServer::Update() {
	this->server->handleClient();
}

bool WebServer::LoadFromSpiffs(String path) {
	String dataType = "text/plain";
	if (path.endsWith("/")) path += "index.htm";

	if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
	else if (path.endsWith(".html")) dataType = "text/html";
	else if (path.endsWith(".htm")) dataType = "text/html";
	else if (path.endsWith(".css")) dataType = "text/css";
	else if (path.endsWith(".js")) dataType = "application/javascript";
	else if (path.endsWith(".png")) dataType = "image/png";
	else if (path.endsWith(".svg")) dataType = "image/svg+xml";
	else if (path.endsWith(".gif")) dataType = "image/gif";
	else if (path.endsWith(".jpg")) dataType = "image/jpeg";
	else if (path.endsWith(".ico")) dataType = "image/x-icon";
	else if (path.endsWith(".xml")) dataType = "text/xml";
	else if (path.endsWith(".pdf")) dataType = "application/pdf";
	else if (path.endsWith(".zip")) dataType = "application/zip";
	File dataFile = SPIFFS.open(path.c_str(), "r");
	if (this->server->hasArg("download")) dataType = "application/octet-stream";
	if (this->server->streamFile(dataFile, dataType) != dataFile.size()) {
	}
	dataFile.close();
	return true;
}

void WebServer::DoHandleRoot() {
	this->server->sendHeader("Location", "/index.html", true);
	this->server->send(302, "text/plane", "");
}

void WebServer::DoHandleWebRequests() {
	if (LoadFromSpiffs(this->server->uri())) return;
	String message = "File Not Detected\n\n";
	message += "URI: ";
	message += this->server->uri();
	message += "\nMethod: ";
	message += (this->server->method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += this->server->args();
	message += "\n";
	for (uint8_t i = 0; i < this->server->args(); i++) {
		message += " NAME:" + this->server->argName(i) + "\n VALUE:" + this->server->arg(i) + "\n";
	}
	this->server->send(404, "text/plain", message);
	if (DEBUG)
		Serial.println(message);
}

void HandleWebRequests() {
	WebServer::getInstance().DoHandleWebRequests();
}

void HandleRoot() {
	WebServer::getInstance().DoHandleRoot();
}
