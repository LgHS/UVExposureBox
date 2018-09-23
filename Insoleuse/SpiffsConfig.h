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
	char TargetSSID[255];
	char TargetPassword[255];
	char APSSID[255];
	char APPassword[255];
	bool APEnabled;
};

class SpiffsConfig {
public:
	static SpiffsConfig& getInstance() {
		static SpiffsConfig instance;
		return instance;
	}

	bool Load() {
		this->LoadFile(CONFIG_FILE_PATH, this->Data);
	}

	bool Save() {
		this->SaveFile(CONFIG_FILE_PATH, this->Data);
	}

	bool LoadDefault() {
		this->SaveFile(DEFAULT_CONFIG_FILE_PATH, this->Data);
	}

	void Stop() {
		SPIFFS.end();
	}

	SpiffsConfigData* Data = new SpiffsConfigData();
private:
	SpiffsConfig() { 
		SPIFFS.begin();
	}

	bool SaveFile(char* path, SpiffsConfigData* data) {
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& json = jsonBuffer.createObject();

		json["target_ssid"] = data->TargetSSID;
		json["target_pwd"] = data->TargetPassword;
		json["ap_ssid"] = data->APSSID;
		json["ap_pwd"] = data->APPassword;
		json["ap_state"] = data->APEnabled;

		File configFile = SPIFFS.open(path, "w");
		if (!configFile) {
			Logger::getInstance().Debug("Failed to open config file for writing");
			return false;
		}

		json.printTo(configFile);

		configFile.flush();
		configFile.close();
		return true;
	}

	bool LoadFile(char* path, SpiffsConfigData* data) {
		File configFile = SPIFFS.open(path, "r");
		if (!configFile) {
			Logger::getInstance().Debug("Cant' open config");
			return LoadDefault();
		}

		size_t size = configFile.size();
		if (size > 1024) {
			Logger::getInstance().Debug("Config too big");
			return LoadDefault();
		}

		String debugLogData;
		while (configFile.available()) {
			debugLogData += char(configFile.read());
		}
		configFile.close();

		Serial.println(debugLogData);

		configFile = SPIFFS.open(path, "r");

		std::unique_ptr<char[]> buf(new char[size]);

		configFile.readBytes(buf.get(), size);

		const size_t bufferSize = JSON_OBJECT_SIZE(5) + 110;
		DynamicJsonBuffer jsonBuffer(bufferSize);

		JsonObject& json = jsonBuffer.parseObject(buf.get());

		configFile.close();

		if (json.success()) {
			strncpy(data->TargetSSID, json["target_ssid"], 256);
			strncpy(data->TargetPassword, json["target_pwd"], 256);
			strncpy(data->APSSID, json["ap_ssid"], 256);
			strncpy(data->APPassword, json["ap_pwd"], 256);
			data->APEnabled = json["ap_state"] ? true : false;
		}
		else {
			Logger::getInstance().Debug("Can't parse json");
			return LoadDefault();
		}
		return true;
	}
};
#endif