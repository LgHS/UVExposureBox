// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "Config.h"
#include <LiquidCrystal_I2C.h>
#include "LiquidMenu/src/LiquidMenu.h"
#include "Keyboard.h"
#include <Keypad.h>
#include <Keypad_MC17.h>

#define WELCOME_SCREEN 0
#define HOME_SCREEN 1
#define START_SCREEN 2

enum MenuFuction {
	A = 1,
	B = 2,
	C = 3,
	D = 4
};

class ApplicationMenu {
public:
	static ApplicationMenu& getInstance() {
		static ApplicationMenu instance;
		return instance;
	}

	void Init();
	void Navigate(int screen);
	void UpdateTime(char* time);
	void Update();
	void SwitchFocus(int count, bool direction);
private:
	ApplicationMenu();

	int currentScreen = -1;
	char* time;

	GPIO* gpio = new GPIO();

	Keyboard* keyboard = new Keyboard();

	LiquidCrystal_I2C*  lcd = new LiquidCrystal_I2C(I2CADDR_LCD, LCD_COL, LCD_ROW);

	LiquidLine* welcome_line1 = new LiquidLine(0, 0, "Insoleuse v", VERSION);
	LiquidLine* welcome_line2 = new LiquidLine(0, 1, "Build by LGHS");
	LiquidLine* welcome_line3 = new LiquidLine(0, 2, "Maintained by EIS");
	LiquidLine* welcome_line4 = new LiquidLine(0, 3, "Under MIT License");
	LiquidScreen* welcome_screen = new LiquidScreen(*welcome_line1, *welcome_line2, *welcome_line3, *welcome_line4);
	
	LiquidLine* home_line1 = new LiquidLine(0, 0, "Select your option");
	LiquidLine* home_line2 = new LiquidLine(0, 1, "A - Start");
	LiquidLine* home_line3 = new LiquidLine(0, 2, "B - Settings");
	LiquidLine* home_line4 = new LiquidLine(0, 3, "");
	LiquidScreen* home_screen = new LiquidScreen(*home_line1, *home_line2, *home_line3, *home_line4);

	LiquidLine* start_line1 = new LiquidLine(0, 0, "Select your time");
	LiquidLine* start_line2 = new LiquidLine(0, 1, "");
	LiquidLine* start_line3 = new LiquidLine(0, 2, "");
	LiquidLine* start_line4 = new LiquidLine(0, 3, "");
	LiquidScreen* start_screen = new LiquidScreen(*start_line1, *start_line2, *start_line3, *start_line4);

	LiquidLine* setting_line1 = new LiquidLine(0, 0, "Select your time");
	LiquidLine* setting_line2 = new LiquidLine(0, 1, "");
	LiquidLine* setting_line3 = new LiquidLine(0, 2, "");
	LiquidLine* setting_line4 = new LiquidLine(0, 3, "");
	LiquidScreen* setting_screen = new LiquidScreen(*setting_line1, *setting_line2, *setting_line3, *setting_line4);

	LiquidMenu* menu = new LiquidMenu(*lcd);
};

#endif

