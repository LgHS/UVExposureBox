#ifndef _SPIFFS_CONFIG_h
#define _SPIFFS_CONFIG_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "Config.h"
#include "WebServer.h"
#include "Json/ArduinoJson.h"
#include "Job.h"
#include "Menu.h"
#include "Logger.h"
#include "TemperatureSensor.h"

struct SpiffsConfigData {
	char TargetSSID[10];
	char TargetPassword[10];
	char APSSID[10];
	char APPassword[10];
	bool APEnabled;
};

class SpiffsConfig {
public:
	static SpiffsConfig& getInstance() {
		static SpiffsConfig instance;
		return instance;
	}

	bool Load() {
		
		File configFile = SPIFFS.open("/config.json", "r");
		if (!configFile) {
			Logger::getInstance().Debug("Cant' open config");
			return false;
		}

		size_t size = configFile.size();
		if (size > 1024) {
			Logger::getInstance().Debug("Config too big");
			return false;
		}

		String debugLogData;
		while (configFile.available()) {
			debugLogData += char(configFile.read());
		}
		configFile.close();

		Serial.println(debugLogData);

		configFile = SPIFFS.open("/config.json", "r");

		std::unique_ptr<char[]> buf(new char[size]);

		configFile.readBytes(buf.get(), size);

		const size_t bufferSize = JSON_OBJECT_SIZE(5) + 110;
		DynamicJsonBuffer jsonBuffer(bufferSize);

		JsonObject& json = jsonBuffer.parseObject(buf.get());

		configFile.close();

		if (json.success()) {
			strncpy(this->Data->TargetSSID, json["target_ssid"], 9);
			strncpy(this->Data->TargetPassword, json["target_pwd"], 9);
			strncpy(this->Data->APSSID, json["ap_ssid"], 9);
			strncpy(this->Data->APPassword, json["ap_pwd"], 9);
			this->Data->APEnabled = json["ap_state"] ? true : false;
		}
		else {
			Logger::getInstance().Debug("Can't parse json");
			return false;
		}
		return true;
	}

	bool Save() {
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& json = jsonBuffer.createObject();

		json["target_ssid"] = this->Data->TargetSSID;
		json["target_pwd"] = this->Data->TargetPassword;
		json["ap_ssid"] = this->Data->APSSID;
		json["ap_pwd"] = this->Data->APPassword;
		json["ap_state"] = this->Data->APEnabled;

		File configFile = SPIFFS.open("/config.json", "w");
		if (!configFile) {
			Logger::getInstance().Debug("Failed to open config file for writing");
			return false;
		}

		json.printTo(configFile);

		configFile.flush();
		configFile.close();
		return true;
	}

	void Stop() {
		SPIFFS.end();
	}

	SpiffsConfigData* Data = new SpiffsConfigData();
private:
	SpiffsConfig() { 
		SPIFFS.begin();
	}
};
#endif