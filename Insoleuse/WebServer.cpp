// 
// 
// 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "Json/ArduinoJson.h"
#include "Config.h"
#include "WebServer.h"
#include "SpiffsConfig.h"
#include "Job.h"
#include "Menu.h"
#include "Logger.h"
#include "TemperatureSensor.h"

void WebServer::Init() {
	Logger::getInstance().Debug("WebServer::Init()");
	if (SpiffsConfig::getInstance().Data->APEnabled || !this->ConnectToWiFi())
		this->StartAP();
	this->StartServer();
}

bool WebServer::ConnectToWiFi() {
	int retryCount = 0;
	Logger::getInstance().Debug("Connect to WiFi SSID:" + String(SpiffsConfig::getInstance().Data->TargetSSID) + " PWD:" + String(SpiffsConfig::getInstance().Data->TargetPassword));
	WiFi.mode(WIFI_STA);
	WiFi.begin(SpiffsConfig::getInstance().Data->TargetSSID, SpiffsConfig::getInstance().Data->TargetPassword);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
		retryCount += 1;
		if (retryCount == WIFI_RETRY_COUNT) {
			return false;
		}
	}
	this->myIP = WiFi.localIP();
	Logger::getInstance().Debug("Connected IP:" + this->myIP.toString());
	SpiffsConfig::getInstance().Data->APEnabled = false;
	return true;
}

void WebServer::StartAP() {
	Logger::getInstance().Debug("Create WiFi SSID:" + String(SpiffsConfig::getInstance().Data->APSSID) + " PWD:" + String(SpiffsConfig::getInstance().Data->APPassword));
	WiFi.mode(WIFI_AP);
	WiFi.softAP(SpiffsConfig::getInstance().Data->APSSID, SpiffsConfig::getInstance().Data->APPassword);
	this->myIP = WiFi.softAPIP();
	Logger::getInstance().Debug("Connected IP:" + this->myIP.toString());
	SpiffsConfig::getInstance().Data->APEnabled = true;
}

void WebServer::StartServer() {
	this->server = new ESP8266WebServer(WEBSERVER_PORT);
	this->server->on("/", HandleRoot);
	this->server->on("/api/getRemainingTime", HandleGetRemainingTime);
	this->server->on("/api/getState", HandleGetState);
	this->server->on("/api/getTemperature", HandleGetTemperature);
	this->server->on("/api/getVersion", HandleGetVersion);
	this->server->on("/api/getConfig", HandleGetConfig);
	this->server->on("/api/pause", HandlePauseJob);
	this->server->on("/api/cancel", HandleCancelJob);
	this->server->on("/api/start", HandleStartJob);
	this->server->onNotFound(HandleWebRequests);
	this->server->begin();
}

void WebServer::Stop() {
	server->stop();
}

void WebServer::Update() {
	this->server->handleClient();
}

bool WebServer::LoadFromSpiffs(String path) {
	Logger::getInstance().Debug("WebServer::LoadFromSpiffs()");
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
	else if (path.endsWith(".mp3")) dataType = "audio/mpeg";
	File dataFile = SPIFFS.open(path.c_str(), "r");
	if (this->server->hasArg("download")) dataType = "application/octet-stream";
	if (this->server->streamFile(dataFile, dataType) != dataFile.size()) {
	}
	dataFile.close();
	return true;
}

void WebServer::DoHandleRoot() {
	Logger::getInstance().Debug("WebServer::HandleRoot()");
	this->server->sendHeader("Location", "/index.html", true);
	this->server->send(302, "text/plane", "");
}

void WebServer::DoHandleWebRequests() {
	Logger::getInstance().Debug("WebServer::HandleWebRequest()");
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
#ifdef DEBUG
	Serial.println(message);
#endif
}

void WebServer::DoHandleGetState() {
	Logger::getInstance().Debug("WebServer::HandleGetState()");
	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.createObject();
	root["running"] = Job::getInstance().IsRunning ? "run" : (Job::getInstance().RemainingTime > 0 ? "pause" : "idle");

	String message;
	root.printTo(message);

	this->server->send(200, "text/json", message);
}

void WebServer::DoHandleGetRemainingTime() {
	Logger::getInstance().Debug("WebServer::HandleGetRemainingTime()");
	if (Job::getInstance().IsRunning) {
		StaticJsonBuffer<200> jsonBuffer;

		JsonObject& root = jsonBuffer.createObject();
		root["remainingTime"] = Job::getInstance().RemainingTime;
		root["refreshRate"] = JOB_REFRESH_RATE;

		getRemainingTimeResponse = "";
		root.printTo(getRemainingTimeResponse);
	}
	this->server->send(200, "text/json", getRemainingTimeResponse);
}

void WebServer::DoHandleGetTemperature() {
	Logger::getInstance().Debug("WebServer::HandleGetTemperature()");

	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.createObject();
	root["temperature"] = TemperatureSensor::getInstance().GetTemp();

	getTempResponse = "";
	root.printTo(getTempResponse);
	this->server->send(200, "text/json", getTempResponse);
}

void WebServer::DoHandleCancelJob() {
	Logger::getInstance().Debug("WebServer::HandleCancelJob()");

	if (ApplicationMenu::getInstance().CurrentScreen == JOB_SCREEN)
		ApplicationMenu::getInstance().BufferedKey = 'C';

	this->server->send(200, "text/json", "");
}

void WebServer::DoHandlePauseJob() {
	Logger::getInstance().Debug("WebServer::HandlePauseJob()");

	if (ApplicationMenu::getInstance().CurrentScreen == JOB_SCREEN)
		ApplicationMenu::getInstance().BufferedKey = 'D';

	this->server->send(200, "text/json", "");
}

void WebServer::DoHandleStartJob() {
	Logger::getInstance().Debug("WebServer::HandleStartJob()");

	int time = -1;
	for (int i = 0; i < this->server->args(); i++) {
		if (this->server->arg(i).length() > 100)
			continue;

		if (this->server->argName(i) == "time") {
			time = this->server->arg(i).toInt();
		}
	}
	if (time > -1) {
		ApplicationMenu::getInstance().SetJobRemainingTime(time);
		Start_Do_A();
	}
	this->server->send(200, "text / plain", "");
}

void WebServer::DoHandleGetVersion() {
	Logger::getInstance().Debug("WebServer::HandleGetVersion()");
	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.createObject();
	root["version"] = VERSION;

	String versionMessage;
	root.printTo(versionMessage);
	this->server->send(200, "text/json", versionMessage);
}

void WebServer::DoHandleGetConfig() {
	Logger::getInstance().Debug("WebServer::HandleGetConfig()");

	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.createObject();
	root["target_ssid"] = SpiffsConfig::getInstance().Data->TargetSSID;
	root["target_pwd"] = SpiffsConfig::getInstance().Data->TargetPassword;
	root["ap_ssid"] = SpiffsConfig::getInstance().Data->APSSID;
	root["ap_pwd"] = SpiffsConfig::getInstance().Data->APPassword;
	root["ap_state"] = SpiffsConfig::getInstance().Data->APEnabled;

	String message;
	root.printTo(message);
	this->server->send(200, "text/json", message);
}

void HandleWebRequests() {
	WebServer::getInstance().DoHandleWebRequests();
}

void HandleRoot() {
	WebServer::getInstance().DoHandleRoot();
}

void HandleGetState() {
	WebServer::getInstance().DoHandleGetState();
}

void HandleGetRemainingTime() {
	WebServer::getInstance().DoHandleGetRemainingTime();
}

void HandleCancelJob() {
	WebServer::getInstance().DoHandleCancelJob();
}

void HandlePauseJob() {
	WebServer::getInstance().DoHandlePauseJob();
}

void HandleStartJob() {
	WebServer::getInstance().DoHandleStartJob();
}

void HandleGetTemperature() {
	WebServer::getInstance().DoHandleGetTemperature();
}

void OnTemperatureTick() {
	TemperatureSensor::getInstance().DoOnTempTick();
}

void HandleGetVersion() {
	WebServer::getInstance().DoHandleGetVersion();
}

void HandleGetConfig() {
	WebServer::getInstance().DoHandleGetConfig();
}