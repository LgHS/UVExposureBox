/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#include "ReedSwitchSecurity.h"
#include "Piezo.h"
#include "UVStrip.h"
#include "Job.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"
#include <Timer.h>
#include "ReedSwitchSecurity.h"

const char* imagefile = "/image.png";
const char* htmlfile = "/index.html";

//ESP AP Mode configuration
const char *ssid = "image-demo-circuits4you.com";
const char *password = "password";


ESP8266WebServer server(80);

bool loadFromSpiffs(String path) {
	String dataType = "text/plain";
	if (path.endsWith("/")) path += "index.htm";

	if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
	else if (path.endsWith(".html")) dataType = "text/html";
	else if (path.endsWith(".htm")) dataType = "text/html";
	else if (path.endsWith(".css")) dataType = "text/css";
	else if (path.endsWith(".js")) dataType = "application/javascript";
	else if (path.endsWith(".png")) dataType = "image/png";
	else if (path.endsWith(".gif")) dataType = "image/gif";
	else if (path.endsWith(".jpg")) dataType = "image/jpeg";
	else if (path.endsWith(".ico")) dataType = "image/x-icon";
	else if (path.endsWith(".xml")) dataType = "text/xml";
	else if (path.endsWith(".pdf")) dataType = "application/pdf";
	else if (path.endsWith(".zip")) dataType = "application/zip";
	File dataFile = SPIFFS.open(path.c_str(), "r");
	if (server.hasArg("download")) dataType = "application/octet-stream";
	if (server.streamFile(dataFile, dataType) != dataFile.size()) {
	}

	dataFile.close();
	return true;
}

void handleRoot() {
	server.sendHeader("Location", "/index.html", true);   //Redirect to our html web page
	server.send(302, "text/plane", "");
}

void handleWebRequests() {
	if (loadFromSpiffs(server.uri())) return;
	String message = "File Not Detected\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
	Serial.println(message);
}


Timer t;

int currentTime = 0;
char timeString[16];

void initializeGPIO() {
	pinMode(RelayPin, OUTPUT);
	pinMode(PiezoPin, OUTPUT);
	pinMode(ReedSwitchPin, INPUT);

	digitalWrite(RelayPin, LOW);
	digitalWrite(PiezoPin, LOW);
}

void setup()
{
	ApplicationMenu::getInstance().Init();
	ApplicationMenu::getInstance().Navigate(WELCOME_SCREEN);

	initializeGPIO();

	Serial.begin(9600);
	Serial.println("LCD...");

	while (!Serial);

	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	ReedSwitchSecurity::getInstance().Init();

	SPIFFS.begin();
	Serial.println("File System Initialized");

	//Initialize AP Mode
	WiFi.softAP(ssid);  //Password not used
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("Web Server IP:");
	Serial.println(myIP);

	//Initialize Webserver
	server.on("/", handleRoot);
	server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI
	server.begin();

	delay(2000);
	
	t.every(100, UpdateScreen);

	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);

	ReedSwitchSecurity::getInstance().Start();
}

void UpdateScreen() {
	ApplicationMenu::getInstance().Update();
}

void loop()
{
	t.update();
	Job::getInstance().Update();
	ReedSwitchSecurity::getInstance().Update();
	server.handleClient();
}