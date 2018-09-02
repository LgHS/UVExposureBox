// ReedSwitchSecurity.h

#ifndef _REEDSWITCHSECURITY_h
#define _REEDSWITCHSECURITY_h

#include <Timer.h>
#include "Arduino.h"
#include "Config.h"
#include "Job.h"
#include "Menu.h"

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
	bool IsPaused = false;

private:
	Timer t;
	ReedSwitchSecurity() { }
};

void OnReedSwitchTick() {

	if (!digitalRead(ReedSwitchPin) && !ReedSwitchSecurity::getInstance().IsPaused) {
		if (Job::getInstance().IsRunning && ApplicationMenu::getInstance().CurrentScreen == COUNTDOWN_SCREEN) {
			Job::getInstance().Stop();
			ReedSwitchSecurity::getInstance().IsPaused = true;
		}
	}
	else if (digitalRead(ReedSwitchPin) && ReedSwitchSecurity::getInstance().IsPaused) {
		if (!Job::getInstance().IsRunning && ApplicationMenu::getInstance().CurrentScreen == COUNTDOWN_SCREEN) {
			Job::getInstance().Start();
			ReedSwitchSecurity::getInstance().IsPaused = false;
		}
	}
	else if (ApplicationMenu::getInstance().CurrentScreen != COUNTDOWN_SCREEN && ReedSwitchSecurity::getInstance().IsPaused == true) {
		ReedSwitchSecurity::getInstance().IsPaused = false;
	}
}

#endif

