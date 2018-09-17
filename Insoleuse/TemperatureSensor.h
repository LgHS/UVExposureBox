#ifndef _TEMPSENSOR_h
#define _TEMPSENSOR_h


#include <Timer.h>
#include "Arduino.h"
#include "Config.h"
#include "GPIO.h"

void OnTemperatureTick();

class TemperatureSensor {
public:
	float lastTemp = 0;

	static TemperatureSensor& getInstance() {
		static TemperatureSensor instance;
		return instance;
	}

	void Init() {
		t = new Timer();
	}

	void Start() {
		t->every(TEMP_REFRESH_RATE_MS, OnTemperatureTick);
	}

	void Update() {
		t->update();
	}

	void DoOnTempTick() {
		int analogValue = analogRead(GPIO::getInstance().TempSensorPin);
		float millivolts = (analogValue / 1024.0) * 2826;
		float celsius = millivolts / 10;

		if (lastTemp != celsius) {
			dtostrf(celsius, 6, 2, this->temp);
			ApplicationMenu::getInstance().SetTemp(this->temp);
			lastTemp = celsius;
		}
	}

	char* GetTemp() {
		return this->temp;
	}
private:
	Timer* t;
	char temp[8]; // Buffer big enough for 7-character float
	TemperatureSensor(){ }
};

#endif
