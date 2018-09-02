// 
// 
// 

#include "Menu.h"
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>
#include "Keyboard.h"
#include <Keypad.h>
#include <Keypad_MC17.h>

ApplicationMenu::ApplicationMenu() {

}

void Do_A() {
	Serial.println("A");
}

void Do_B() {
	Serial.println("B");
}

void ApplicationMenu::Init() {
	this->keyboard->Init();

	this->lcd->init();
	this->lcd->backlight();

	this->menu->init();

	this->home_line1->attach_function(A, Do_A);
	this->home_line1->attach_function(B, Do_B);

	this->menu->add_screen(*this->welcome_screen);
	this->menu->add_screen(*this->home_screen);

	this->menu->update();
}

void ApplicationMenu::Navigate(int screen) {
	if (screen == this->currentScreen) return;
	this->menu->change_screen(screen + 1);
	this->currentScreen = screen;
}

void ApplicationMenu::UpdateTime(char * newtime) {
	//if (strcmp(this->time, newtime) == 0) return;

	this->time = newtime;
	this->menu->update();
}

void ApplicationMenu::Update() {
	
	char key = this->keyboard->GetKey();

	if (key) {
		tone(this->gpio->Piezo, 440, 250);


		if (key == 'A') {
			Serial.println(key);
			this->menu->call_function(A);
		}
		if (key == 'B') {
			Serial.println(key);
			this->menu->call_function(B);
		}
		if (key == 'C') {
			this->menu->call_function(C);
		}
		if (key == 'D') {
			this->menu->call_function(D);
		}
	}

	//if (left.check() == LOW) {
	//	menu.previous_screen();
	//}
	//if (up.check() == LOW) {
	//	// Calls the function identified with
	//	// increase or 1 for the focused line.
	//	menu.call_function(increase);
	//}
	//if (down.check() == LOW) {
	//	menu.call_function(decrease);
	//}
	//if (enter.check() == LOW) {
	//	// Switches focus to the next line.
	//	menu.switch_focus();
	//}
}