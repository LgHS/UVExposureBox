/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/
#include "GPIO.h"
#include "WebServer.h"
#include "ReedSwitchSecurity.h"
#include "Piezo.h"
#include "UVStrip.h"
#include "Job.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"
#include <Timer.h>
#include "ReedSwitchSecurity.h"

void setup()
{
	ApplicationMenu::getInstance().Init();
	ApplicationMenu::getInstance().Navigate(WELCOME_SCREEN);

	GPIO::getInstance().InitializeGPIO();

	Serial.begin(9600);

	while (!Serial);

	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	ReedSwitchSecurity::getInstance().Init();
	
	WebServer::getInstance().Init();

	delay(2000);

	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);

	ReedSwitchSecurity::getInstance().Start();
}

void loop()
{
	ApplicationMenu::getInstance().Update();
	Job::getInstance().Update();
	ReedSwitchSecurity::getInstance().Update();
	WebServer::getInstance().Update();
}