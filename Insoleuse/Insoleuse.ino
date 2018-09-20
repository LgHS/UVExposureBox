/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/

#include <FS.h>
#include "GPIO.h"
#include "WebServer.h"
#include "ReedSwitchSecurity.h"
#include "Job.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"
#include "TemperatureSensor.h"
#include "SpiffsConfig.h"

void setup()
{
	Serial.begin(9600);
	while (!Serial);
	
	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	ApplicationMenu::getInstance().Init();
	ApplicationMenu::getInstance().Navigate(WELCOME_SCREEN);

	SpiffsConfig::getInstance().Load();
	
	GPIO::getInstance().Init();

	ReedSwitchSecurity::getInstance().Init();
	TemperatureSensor::getInstance().Init();
	
	WebServer::getInstance().Init();

	ReedSwitchSecurity::getInstance().Start();
	TemperatureSensor::getInstance().Start();
	
	ApplicationMenu::getInstance().Navigate(HOME_SCREEN);
}

void restart() {
	WebServer::getInstance().Stop();
	Job::getInstance().Stop();
	ReedSwitchSecurity::getInstance().Stop();
	TemperatureSensor::getInstance().Stop();
	SpiffsConfig::getInstance().Stop();
	ESP.restart();
}

void loop()
{
	WebServer::getInstance().Update();
	ApplicationMenu::getInstance().Update();
	Job::getInstance().Update();
	ReedSwitchSecurity::getInstance().Update();
	TemperatureSensor::getInstance().Update();

	if (ApplicationMenu::getInstance().RequestRestart == true) {
		restart();
	}
}