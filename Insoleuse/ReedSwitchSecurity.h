// ReedSwitchSecurity.h

#ifndef _REEDSWITCHSECURITY_h
#define _REEDSWITCHSECURITY_h

#include <Timer.h>
#include "Arduino.h"
#include "Config.h"
#include "Job.h"
#include "Menu.h"
#include "Piezo.h"
#include "GPIO.h"

void OnReedSwitchTick();

class ReedSwitchSecurity {
public:
	static ReedSwitchSecurity& getInstance() {
		static ReedSwitchSecurity instance;
		return instance;
	}
	void Init() {
	}
	void Start() {
		t.every(100, OnReedSwitchTick);
	}
	void Update() {
		t.update();
	}
	void OnTick() {

		if (!digitalRead(GPIO::getInstance().ReedSwitchPin) && !IsPaused) {
			if (Job::getInstance().IsRunning && ApplicationMenu::getInstance().CurrentScreen == COUNTDOWN_SCREEN) {
				Job::getInstance().Stop();
				IsPaused = true;
				Piezo::getInstance().Tone(C5, 250);
			}
		}
		else if (digitalRead(GPIO::getInstance().ReedSwitchPin) && IsPaused) {
			if (!Job::getInstance().IsRunning && ApplicationMenu::getInstance().CurrentScreen == COUNTDOWN_SCREEN) {
				Job::getInstance().Start();
				IsPaused = false;
				Piezo::getInstance().Tone(C6, 250);
			}
		}
		else if (ApplicationMenu::getInstance().CurrentScreen != COUNTDOWN_SCREEN && IsPaused == true) {
			IsPaused = false;
		}
	}
private:
	bool IsPaused = false;
	Timer t;
	ReedSwitchSecurity() { }
};

void OnReedSwitchTick() {
	ReedSwitchSecurity::getInstance().OnTick();
}

#endif

