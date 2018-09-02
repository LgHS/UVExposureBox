/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/

#include "ReedSwitchSecurity.h"
#include "Piezo.h"
#include "UVStrip.h"
#include "Job.h"
#include "Screens.h"
#include "MenuFunctions.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"
#include <Timer.h>
#include "ReedSwitchSecurity.h"

Timer t;

int currentTime = 0;
char timeString[16];

void initializeGPIO() {
	pinMode(RelayPin, OUTPUT);
	pinMode(PiezoPin, OUTPUT);
	pinMode(ReedSwitchPin, INPUT);

	digitalWrite(RelayPin, LOW);
	digitalWrite(PiezoPin, LOW);
}

void setup()
{
	ApplicationMenu::getInstance().Init();
	ApplicationMenu::getInstance().Navigate(WELCOME_SCREEN);

	initializeGPIO();

	Serial.begin(9600);
	Serial.println("LCD...");

	while (!Serial);

	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	ReedSwitchSecurity::getInstance().Init();

	delay(2000);
	
	t.every(100, UpdateScreen);

	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);

	ReedSwitchSecurity::getInstance().Start();
}

void UpdateScreen() {
	ApplicationMenu::getInstance().Update();
}

void loop()
{
	t.update();
	Job::getInstance().Update();
	ReedSwitchSecurity::getInstance().Update();
}