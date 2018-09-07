// 
// 
// 

#include "Menu.h"
#include <LiquidCrystal_I2C.h>
#include "LiquidMenu/src/LiquidMenu.h"
#include "Keyboard.h"
#include <Keypad.h>
#include <Keypad_MC17.h>
#include "Job.h"
#include "Piezo.h"

ApplicationMenu::ApplicationMenu() {

}

void ApplicationMenu::Init() {
	this->keyboard->Init();

	this->lcd->init();
	this->lcd->backlight();

	this->menu->init();
	
	this->menu->add_screen(*this->welcomeScreen->Screen);
	this->menu->add_screen(*this->homeScreen->Screen);
	this->menu->add_screen(*this->startScreen->Screen);
	this->menu->add_screen(*this->settingScreen->Screen);
	this->menu->add_screen(*this->jobScreen->Screen);
	
	this->menu->update();
}

void ApplicationMenu::Navigate(int screen) {
	if (screen == this->CurrentScreen) return;
	this->menu->change_screen(screen + 1);
	this->CurrentScreen = screen;
}

void ApplicationMenu::UpdateStartDisplayedTime(char * newtime) {
	this->startScreen->StartScreenTime = newtime;
	this->menu->update();
}

void ApplicationMenu::SetJobRemainingTime(int countdown) {
	int hour = countdown / 3600;
	countdown = countdown % 3600;
	int min = countdown / 60;
	countdown = countdown % 60;
	int sec = countdown;
	   
	memcpy(this->remaningJobTime, this->timeTemplate, sizeof(this->timeTemplate));

	for (int i = 0; i < 8; i++) {
		if (i == 2 || i == 5) continue;

		if (i == 0 && hour != 0) this->remaningJobTime[i] = (char)((hour / 10) + 48);
		else if (i == 1 && hour != 0) this->remaningJobTime[i] = (char)((hour % 10) + 48);
		else if (i == 3 && min != 0) this->remaningJobTime[i] = (char)((min / 10) + 48);
		else if (i == 4 && min != 0) this->remaningJobTime[i] = (char)((min % 10) + 48);
		else if (i == 6 && sec != 0) this->remaningJobTime[i] = (char)((sec / 10) + 48);
		else if (i == 7 && sec != 0) this->remaningJobTime[i] = (char)((sec % 10) + 48);
	}

	if (hour == 0) { this->remaningJobTime[0] = '0'; this->remaningJobTime[1] = '0'; }
	if (min == 0)  { this->remaningJobTime[3] = '0'; this->remaningJobTime[4] = '0'; }
	if (sec == 0)  { this->remaningJobTime[6] = '0'; this->remaningJobTime[7] = '0'; }

	this->jobScreen->CountdownTime = this->remaningJobTime;
	this->menu->update();
}

void ApplicationMenu::CleanLCDVariable() {
	memset(this->jobScreen->CountdownTime, 0, sizeof(this->jobScreen->CountdownTime));
	memset(this->remainingTime, 0, sizeof(this->remainingTime));
	memset(this->remaningJobTime, 0, sizeof(this->remaningJobTime));
	memset(this->startScreen->StartScreenTime, 0, sizeof(this->startScreen->StartScreenTime));
}

void ApplicationMenu::Update() {
	char key = this->keyboard->GetKey();

	if (key) {

		if (key == 'A') {
			Piezo::getInstance().Tone(F4, 250);
			this->menu->call_function(KPA);
		}
		if (key == 'B') {
			Piezo::getInstance().Tone(G4, 250);
			this->menu->call_function(KPB);
		}
		if (key == 'C') {
			Piezo::getInstance().Tone(A4, 250);
			this->menu->call_function(KPC);
		}
		if (key == 'D') {
			Piezo::getInstance().Tone(B4, 250);
			this->menu->call_function(KPD);
		}
		if (key == '0') {
			Piezo::getInstance().Tone(C5, 250);
			this->menu->call_function(KPD0);
		}
		if (key == '1') {
			Piezo::getInstance().Tone(DD5, 250);
			this->menu->call_function(KPD1);
		}
		if (key == '2') {
			Piezo::getInstance().Tone(E5, 250);
			this->menu->call_function(KPD2);
		}
		if (key == '3') {
			Piezo::getInstance().Tone(F5, 250);
			this->menu->call_function(KPD3);
		}
		if (key == '4') {
			Piezo::getInstance().Tone(G5, 250);
			this->menu->call_function(KPD4);
		}
		if (key == '5') {
			Piezo::getInstance().Tone(A5, 250);
			this->menu->call_function(KPD5);
		}
		if (key == '6') {
			Piezo::getInstance().Tone(B5, 250);
			this->menu->call_function(KPD6);
		}
		if (key == '7') {
			Piezo::getInstance().Tone(C6, 250);
			this->menu->call_function(KPD7);
		}
		if (key == '8') {
			Piezo::getInstance().Tone(DD6, 250);
			this->menu->call_function(KPD8);
		}
		if (key == '9') {
			Piezo::getInstance().Tone(E6, 250);
			this->menu->call_function(KPD9);
		}
		if (key == '*') {
			Piezo::getInstance().Tone(F5, 250);
			this->menu->call_function(KPDStar);
		}
		if (key == '#') {
			Piezo::getInstance().Tone(G5, 250);
			this->menu->call_function(KPDSharp);
		}
	}
}

int ApplicationMenu::GetSeconds() {
	int seconds = 0;
	for (int i = 0; i < 8; i++) {
		int value = (int)remainingTime[i] - 48;

		if (i == 0) seconds += value * 60 * 60 * 10;
		else if (i == 1) seconds += value * 60 * 60;
		else if (i == 2)  ;
		else if (i == 3) seconds += value * 60 * 10;
		else if (i == 4) seconds += value * 60;
		else if (i == 5)  ;
		else if (i == 6) seconds += value * 10;
		else if (i == 7) seconds += value;
	}
	return seconds;
}

void ApplicationMenu::SetSettingsIp(char * ip) {
	this->settingScreen->Ip = ip;
}

void ApplicationMenu::ResetTime() {
	memcpy(remainingTime, timeTemplate, sizeof(timeTemplate));
	UpdateStartDisplayedTime(remainingTime);
	currentCaretPosition = 0;
}

void ApplicationMenu::PushNumber(char newNumber) {
	if (remainingTime[currentCaretPosition] == ':') currentCaretPosition += 1;
	if (!IsValidDigitalInput(newNumber, currentCaretPosition)) return;
	remainingTime[currentCaretPosition] = newNumber;
	currentCaretPosition += 1;
	if (currentCaretPosition >= 8) currentCaretPosition = 0;
}

void Home_Do_A() {
	ApplicationMenu::getInstance().Navigate(START_SCREEN);
	ApplicationMenu::getInstance().ResetTime();
}

void Home_Do_B() {
	ApplicationMenu::getInstance().SetSettingsIp(WebServer::getInstance().GetIp());
	ApplicationMenu::getInstance().Navigate(SETTING_SCREEN);
}

void Start_Do_A() {
	ApplicationMenu::getInstance().Navigate(COUNTDOWN_SCREEN);
	Job::getInstance().SetDuration(ApplicationMenu::getInstance().GetSeconds());
	Job::getInstance().Start();
}

void Start_Do_D() {
	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);
}

void Start_Do_D0() {
	ApplicationMenu::getInstance().PushNumber('0');
}
void Start_Do_D1() {
	ApplicationMenu::getInstance().PushNumber('1');
}
void Start_Do_D2() {
	ApplicationMenu::getInstance().PushNumber('2');
}
void Start_Do_D3() {
	ApplicationMenu::getInstance().PushNumber('3');
}
void Start_Do_D4() {
	ApplicationMenu::getInstance().PushNumber('4');
}
void Start_Do_D5() {
	ApplicationMenu::getInstance().PushNumber('5');
}
void Start_Do_D6() {
	ApplicationMenu::getInstance().PushNumber('6');
}
void Start_Do_D7() {
	ApplicationMenu::getInstance().PushNumber('7');
}
void Start_Do_D8() {
	ApplicationMenu::getInstance().PushNumber('8');
}
void Start_Do_D9() {
	ApplicationMenu::getInstance().PushNumber('9');
}

bool IsValidDigitalInput(char c, int position) {
	int value = (int)c - 48;
	if (position == 0) return true;
	else if (position == 1) return true;
	else if (position == 2) return false;
	else if (position == 3) return value >= 0 && value <= 5;
	else if (position == 4) return true;
	else if (position == 5) return false;
	else if (position == 6) return value >= 0 && value <= 5;
	else if (position == 7) return true;
}

void Countdown_Do_C() {
	Job::getInstance().Stop();
	Job::getInstance().Reset();
	ApplicationMenu::getInstance().CleanLCDVariable();
	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);
}

void Countdown_Do_D() {
	if (Job::getInstance().IsRunning)
		Job::getInstance().Stop();
	else
		Job::getInstance().Start();
}

void Settings_Do_D() {
	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);
}