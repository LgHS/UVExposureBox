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

void ApplicationMenu::SwitchFocus(int count, bool direction) {
	for(int i = 0; i < count; i++)
		this->menu->switch_focus(direction);
}

void Do_A() {
	ApplicationMenu::getInstance().Navigate(START_SCREEN);
}

void Do_B() {
	Serial.println("B");
}

void ApplicationMenu::Init() {
	this->keyboard->Init();

	this->lcd->init();
	this->lcd->backlight();

	this->menu->init();

	this->home_screen->attach_function(A, Do_A);
	this->home_screen->attach_function(B, Do_B);
	
	this->menu->add_screen(*this->welcome_screen);
	this->menu->add_screen(*this->home_screen);
	this->menu->add_screen(*this->start_screen);
	
	this->menu->update();
}

void ApplicationMenu::Navigate(int screen) {
	if (screen == this->currentScreen) return;
	this->menu->change_screen(screen + 1);
	this->currentScreen = screen;
}

void ApplicationMenu::UpdateTime(char * newtime) {
	this->time = newtime;
	this->menu->softUpdate();
}

void ApplicationMenu::Update() {
	
	char key = this->keyboard->GetKey();

	if (key) {
		tone(this->gpio->Piezo, 440, 250);

		if (key == 'A') {
			this->menu->call_function(A);
		}
		if (key == 'B') {
			this->menu->call_function(B);
		}
		if (key == 'C') {
			this->menu->switch_focus(true);
		}
		if (key == 'D') {
			this->menu->switch_focus(false);
		}
	}
}