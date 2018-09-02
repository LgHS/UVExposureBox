// UVStrip.h

#ifndef _UVSTRIP_h
#define _UVSTRIP_h

#include "Config.h"
#include "Arduino.h"

class UVStrip {
public:
	static UVStrip& getInstance() {
		static UVStrip instance;
		return instance;
	}
	void Start() {
		digitalWrite(RelayPin, HIGH);
	}
	void Stop() {
		digitalWrite(RelayPin, LOW);
	}
private:
	UVStrip() { };
};

#endif

