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
	D_5 = 587,
	E5 = 659,
	F5 = 698,
	G5 = 783,
	A5 = 880,
	B5 = 987,
	C6 = 1046,
	D_6 = 1174,
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
		Tone(C5, END_TUNE_DURATION);
		delay(END_TUNE_DURATION);
		Tone(C6, END_TUNE_DURATION);
		delay(END_TUNE_DURATION);
		Tone(C5, END_TUNE_DURATION);
		delay(END_TUNE_DURATION);
		Tone(G5, END_TUNE_DURATION);
		delay(END_TUNE_DURATION);
		Tone(C5, END_TUNE_DURATION);
		delay(END_TUNE_DURATION);
		Tone(E5, END_TUNE_DURATION);
		delay(END_TUNE_DURATION);
	}
private:
	Piezo() { };
};


#endif

