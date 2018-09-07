// 
// 
// 

#include "Job.h"
#include <Timer.h>
#include "Config.h"
#include "Menu.h"
#include "Piezo.h"
#include "UVStrip.h"

void Job::SetDuration(int time) {
	this->RemainingTime = time * JOB_REFRESH_RATE;
}

void DecreaseRemainingTime() {
	Job::getInstance().RemainingTime -= 1;
	if (Job::getInstance().RemainingTime <= 0) {
		Job::getInstance().Stop();
		ApplicationMenu::getInstance().Navigate(HOME_SCREEN);
		Job::getInstance().IsRunning = false;
		return;
	}
	if (Job::getInstance().RemainingTime % JOB_REFRESH_RATE == 0) {
		ApplicationMenu::getInstance().SetJobRemainingTime(Job::getInstance().RemainingTime / JOB_REFRESH_RATE);
	}
}

void Job::Start() {
	t.stop(0);
	t.every(1000 / JOB_REFRESH_RATE, DecreaseRemainingTime, this->RemainingTime);
	UVStrip::getInstance().Start();
	ApplicationMenu::getInstance().SetJobRemainingTime(Job::getInstance().RemainingTime / JOB_REFRESH_RATE);
	this->IsRunning = true;
}

void Job::Stop() {
	UVStrip::getInstance().Stop();
	t.stop(0);
	if (this->RemainingTime <= 0) {
		Piezo::getInstance().PlayEndJobTune();
		ApplicationMenu::getInstance().CleanLCDVariable();
	}
	this->IsRunning = false;
}

void Job::Reset() {
	this->RemainingTime = 0;
	this->IsRunning = false;
}

void Job::Update() {
	t.update();
}



