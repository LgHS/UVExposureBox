// 
// 
// 

#include "Menu.h"
#include <LiquidCrystal_I2C.h>
#include <LiquidMenu.h>

ApplicationMenu::ApplicationMenu() {

}

void ApplicationMenu::Init() {
	this->lcd->init();
	this->lcd->backlight();

	this->menu->init();
	this->menu->add_screen(*this->welcome_screen);
	this->menu->add_screen(*this->home_screen);
}

void ApplicationMenu::Navigate(int screen) {
	if (screen == this->currentScreen) return;
	this->menu->change_screen(screen + 1);
	this->currentScreen = screen;
}