#pragma once
#ifndef _LOGGER_h
#define _LOGGER_h

#include "Config.h"

class Logger {
public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void Debug(String message) {
#ifdef DEBUG
		this->Log(message);
#endif // DEBUG
	}

	void Log(String message) {
		Serial.println(message);
	}

private:
	Logger() {

	}
};

#endif