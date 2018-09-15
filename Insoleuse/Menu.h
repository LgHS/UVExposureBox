// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "Config.h"
#include <LiquidCrystal_I2C.h>
#include "LiquidMenu/src/LiquidMenu.h"
#include "Timer.h"
#include "WebServer.h"
#include "Keyboard.h"
#include <Keypad.h>
#include <Keypad_MC17.h>

enum MenuFuction {
	KPA = 1,
	KPB = 2,
	KPC = 3,
	KPD = 4,
	KPD0 = 5,
	KPD1 = 6,
	KPD2 = 7,
	KPD3 = 8,
	KPD4 = 9,
	KPD5 = 10,
	KPD6 = 11,
	KPD7 = 12,
	KPD8 = 13,
	KPD9 = 14,
	KPDStar = 15,
	KPDSharp = 16
};

void Home_Do_A();
void Home_Do_B();
void Start_Do_A();
void Start_Do_D();
void Start_Do_D0();
void Start_Do_D1();
void Start_Do_D2();
void Start_Do_D3();
void Start_Do_D4();
void Start_Do_D5();
void Start_Do_D6();
void Start_Do_D7();
void Start_Do_D8();
void Start_Do_D9();
void Job_Do_D();
void Job_Do_C();
void Settings_Do_D();

class WelcomeScreen {
private:
	LiquidLine* welcome_line1 = new LiquidLine(0, 0, "Insoleuse v", VERSION);
	LiquidLine* welcome_line2 = new LiquidLine(0, 1, "Build by LGHS");
	LiquidLine* welcome_line3 = new LiquidLine(0, 2, "Maintained by EIS");
	LiquidLine* welcome_line4 = new LiquidLine(0, 3, "Under MIT License");
public:
	LiquidScreen* Screen = new LiquidScreen(*welcome_line1, *welcome_line2, *welcome_line3, *welcome_line4);
};

class HomeScreen {
private:
	LiquidLine* home_line1 = new LiquidLine(0, 0, "Select your option");
	LiquidLine* home_line2 = new LiquidLine(0, 1, "A:Start");
	LiquidLine* home_line3 = new LiquidLine(0, 2, "B:Settings");
	LiquidLine* home_line4 = new LiquidLine(0, 3, "");
public:
	HomeScreen() {
		this->Screen->attach_function(KPA, Home_Do_A);
		this->Screen->attach_function(KPB, Home_Do_B);
	}
	LiquidScreen* Screen = new LiquidScreen(*home_line1, *home_line2, *home_line3, *home_line4);
};

class StartScreen {
private:
	LiquidLine* start_line1 = new LiquidLine(0, 0, "Select your time    ");
	LiquidLine* start_line2 = new LiquidLine(0, 1, StartScreenTime);
	LiquidLine* start_line3 = new LiquidLine(0, 2, "A:Start             ");
	LiquidLine* start_line4 = new LiquidLine(0, 3, "C:Clear D:Return    ");
public:
	char* StartScreenTime;
	LiquidScreen* Screen = new LiquidScreen(*start_line1, *start_line2, *start_line3, *start_line4);

	StartScreen() {
		this->Screen->attach_function(KPA, Start_Do_A);
		this->Screen->attach_function(KPD, Start_Do_D);
		this->Screen->attach_function(KPC, Home_Do_A);
		this->Screen->attach_function(KPD0, Start_Do_D0);
		this->Screen->attach_function(KPD1, Start_Do_D1);
		this->Screen->attach_function(KPD2, Start_Do_D2);
		this->Screen->attach_function(KPD3, Start_Do_D3);
		this->Screen->attach_function(KPD4, Start_Do_D4);
		this->Screen->attach_function(KPD5, Start_Do_D5);
		this->Screen->attach_function(KPD6, Start_Do_D6);
		this->Screen->attach_function(KPD7, Start_Do_D7);
		this->Screen->attach_function(KPD8, Start_Do_D8);
		this->Screen->attach_function(KPD9, Start_Do_D9);
	}
};

class JobScreen {
private:
	LiquidLine* line1 = new LiquidLine(0, 0, "UV running          ");
	LiquidLine* line3 = new LiquidLine(0, 1, "Time rem.  ", CountdownTime);
	LiquidLine* line2 = new LiquidLine(0, 2, "");
	LiquidLine* line4 = new LiquidLine(0, 3, "C:Cancel D:Pause    ");
public:
	char* CountdownTime;
	JobScreen() {
		this->Screen->attach_function(KPC, Job_Do_C);
		this->Screen->attach_function(KPD, Job_Do_D);
	}
	LiquidScreen* Screen = new LiquidScreen(*line1, *line2, *line3, *line4);
};

class SettingScreen {
private:
	LiquidLine* setting_line1 = new LiquidLine(0, 0, "IP   :", Ip);
	LiquidLine* setting_line3 = new LiquidLine(0, 1, "SSID :", WEBSERVER_SSID);
	LiquidLine* setting_line2 = new LiquidLine(0, 2, "Pwd  :", WEBSERVER_PWD);
	LiquidLine* setting_line4 = new LiquidLine(0, 3, "D:Return");
public:
	char* Ip;
	LiquidScreen* Screen = new LiquidScreen(*setting_line1, *setting_line2, *setting_line3, *setting_line4);
	SettingScreen() {
		this->Screen->attach_function(KPD, Settings_Do_D);
	}
};

class ApplicationMenu {
public:
	static ApplicationMenu& getInstance() {
		static ApplicationMenu instance;
		return instance;
	}

	void Init();
	void Navigate(int screen);
	void Update();
	int GetSeconds();
	void SetJobRemainingTime(int countdown);
	void SetSettingsIp(char* ip);
	void CleanLCDVariable();
	void PushNumber(char newNumber);
	void ResetTime();
	   
	int CurrentScreen = -1;
	char BufferedKey;
private:
	int currentCaretPosition = 0;
	const char timeTemplate[8] = { 'h','h',':','m','m',':','s','s' };
	char * remainingTime = "hh:mm:ss";
	char * remaningJobTime = "hh:mm:ss";
	
	Timer* t = new Timer();
	
	Keyboard* keyboard = new Keyboard();

	LiquidCrystal_I2C*  lcd = new LiquidCrystal_I2C(I2CADDR_LCD, LCD_COL, LCD_ROW);
	   	 
	HomeScreen* homeScreen = new HomeScreen();
	WelcomeScreen* welcomeScreen = new WelcomeScreen();
	StartScreen* startScreen = new StartScreen();
	SettingScreen* settingScreen = new SettingScreen();
	JobScreen* jobScreen = new JobScreen();

	LiquidMenu* menu = new LiquidMenu(*lcd);

	ApplicationMenu();

	bool IsValidDigitalInput(char c, int position);
	void UpdateStartDisplayedTime(char* time);
	void ExecuteKey(char key);
};

#endif

