// UVStrip.h

#ifndef _UVSTRIP_h
#define _UVSTRIP_h

#include "Config.h"
#include "Arduino.h""
#include "GPIO.h"

class UVStrip {
public:
	static UVStrip& getInstance() {
		static UVStrip instance;
		return instance;
	}
	void Start() {
		digitalWrite(GPIO::getInstance().RelayPin, HIGH);
	}
	void Stop() {
		digitalWrite(GPIO::getInstance().RelayPin, LOW);
	}
private:
	UVStrip() { };
};

#endif

