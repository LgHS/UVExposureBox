/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/

#include "GPIO.h"
#include "WebServer.h"
#include "ReedSwitchSecurity.h"
#include "Job.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"
#include "TemperatureSensor.h"

void setup()
{
	Serial.begin(9600);
	while (!Serial);
	
	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	ApplicationMenu::getInstance().Init();
	ApplicationMenu::getInstance().Navigate(WELCOME_SCREEN);

	GPIO::getInstance().Init();

	ReedSwitchSecurity::getInstance().Init();
	TemperatureSensor::getInstance().Init();
	
	WebServer::getInstance().Init();

	delay(2000);

	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);

	ReedSwitchSecurity::getInstance().Start();
	TemperatureSensor::getInstance().Start();
}

void loop()
{
	WebServer::getInstance().Update();
	ApplicationMenu::getInstance().Update();
	Job::getInstance().Update();
	ReedSwitchSecurity::getInstance().Update();
	TemperatureSensor::getInstance().Update();
}