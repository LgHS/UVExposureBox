// 
// 
// 

#include "Menu.h"
#include <LiquidCrystal_I2C.h>
#include "LiquidMenu/src/LiquidMenu.h"
#include "Keyboard.h"
#include <Keypad.h>
#include <Keypad_MC17.h>

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
	
	this->menu->update();
}

void ApplicationMenu::Navigate(int screen) {
	if (screen == this->currentScreen) return;
	this->menu->change_screen(screen + 1);
	this->currentScreen = screen;
}

void ApplicationMenu::UpdateTime(char * newtime) {
	this->startScreen->Time = newtime;
	this->menu->update();
}

void ApplicationMenu::Update() {
	
	char key = this->keyboard->GetKey();

	if (key) {
		tone(this->gpio->Piezo, 440, 250);

		if (key == 'A') {
			this->menu->call_function(KPA);
		}
		if (key == 'B') {
			this->menu->call_function(KPB);
		}
		if (key == 'C') {
			this->menu->call_function(KPC);
		}
		if (key == 'D') {
			this->menu->call_function(KPD);
		}
		if (key == '0') {
			this->menu->call_function(KPD0);
		}
		if (key == '1') {
			this->menu->call_function(KPD1);
		}
		if (key == '2') {
			this->menu->call_function(KPD2);
		}
		if (key == '3') {
			this->menu->call_function(KPD3);
		}
		if (key == '4') {
			this->menu->call_function(KPD4);
		}
		if (key == '5') {
			this->menu->call_function(KPD5);
		}
		if (key == '6') {
			this->menu->call_function(KPD6);
		}
		if (key == '7') {
			this->menu->call_function(KPD7);
		}
		if (key == '8') {
			this->menu->call_function(KPD8);
		}
		if (key == '9') {
			this->menu->call_function(KPD9);
		}
		if (key == '*') {
			this->menu->call_function(KPDStar);
		}
		if (key == '#') {
			this->menu->call_function(KPDSharp);
		}
	}
}

int currentPosition = 0;

void Home_Do_A() {
	ApplicationMenu::getInstance().Navigate(START_SCREEN);
	memcpy(ApplicationMenu::getInstance().remainingTime, ApplicationMenu::getInstance().timeTemplate, sizeof(ApplicationMenu::getInstance().timeTemplate));
	ApplicationMenu::getInstance().UpdateTime(ApplicationMenu::getInstance().remainingTime);
	currentPosition = 0;
}

void Home_Do_B() {
	ApplicationMenu::getInstance().Navigate(SETTING_SCREEN);
}


void Start_Do_A() {
	//TODO: Start Job
}

void Start_Do_D() {
	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);
}

void Start_Do_D0() {
	PushNumber('0');
}
void Start_Do_D1() {
	PushNumber('1');
}
void Start_Do_D2() {
	PushNumber('2');
}
void Start_Do_D3() {
	PushNumber('3');
}
void Start_Do_D4() {
	PushNumber('4');
}
void Start_Do_D5() {
	PushNumber('5');
}
void Start_Do_D6() {
	PushNumber('6');
}
void Start_Do_D7() {
	PushNumber('7');
}
void Start_Do_D8() {
	PushNumber('8');
}
void Start_Do_D9() {
	PushNumber('9');
}

void PushNumber(char newNumber) {
	if (ApplicationMenu::getInstance().remainingTime[currentPosition] == ':') currentPosition += 1;
	if (!IsValidDigitalInput(newNumber, currentPosition)) return;
	ApplicationMenu::getInstance().remainingTime[currentPosition] = newNumber;
	currentPosition += 1;
	if (currentPosition >= 8) currentPosition = 0;
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