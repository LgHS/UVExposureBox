// Piezo.h

#ifndef _PIEZO_h
#define _PIEZO_h

#include "Config.h"
#include "GPIO.h"

enum Note {
	F4 = 349,
	G4 = 392,
	A4 = 440,
	B4 = 493,
	C5 = 523,
	DD5 = 587,
	E5 = 659,
	F5 = 698,
	G5 = 783,
	A5 = 880,
	B5 = 987,
	C6 = 1046,
	DD6 = 1174,
	E6 = 1318,
	F6 = 1396,
	G6 = 1567,
};

class Piezo {
public:
	static Piezo& getInstance() {
		static Piezo instance;
		return instance;
	}
	void Tone(int frequency, int duration) {
		tone(GPIO::getInstance().PiezoPin, frequency, duration);
	}

	void PlayEndJobTune() {
		int duration = 500;
		Tone(C5, duration);
		delay(duration);
		Tone(C6, duration);
		delay(duration);
		Tone(C5, duration);
		delay(duration);
		Tone(G5, duration);
		delay(duration);
		Tone(C5, duration);
		delay(duration);
		Tone(E5, duration);
		delay(duration);
	}
private:
	Piezo() { };
};


#endif

