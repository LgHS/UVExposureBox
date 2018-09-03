// GPIO.h

#ifndef _GPIO_h
#define _GPIO_h

#include "arduino.h"

class GPIO {
public:
	static GPIO& getInstance() {
		static GPIO instance;
		return instance;
	}

	uint8_t RelayPin = D8;
	uint8_t PiezoPin = D7;
	uint8_t ReedSwitchPin = D6;
	
	void InitializeGPIO() {
		pinMode(RelayPin, OUTPUT);
		pinMode(PiezoPin, OUTPUT);
		pinMode(ReedSwitchPin, INPUT);

		digitalWrite(RelayPin, LOW);
		digitalWrite(PiezoPin, LOW);
	}
private:
	GPIO() { }
};

#endif

