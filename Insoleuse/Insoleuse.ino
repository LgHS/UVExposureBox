/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/

#include "Keyboard.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"
#include <Timer.h>

ApplicationMenu* menu = new ApplicationMenu();
GPIO* gpio = new GPIO();
Timer t;

int currentTime = 0;
char timeString[16];

void initializeGPIO() {
	pinMode(gpio->Relay, OUTPUT);
	pinMode(gpio->Piezo, OUTPUT);
	pinMode(gpio->ReedSwitch, INPUT);

	digitalWrite(gpio->Relay, LOW);
	digitalWrite(gpio->Piezo, LOW);
}

void setup()
{
	menu->Init();
	menu->Navigate(WELCOME_SCREEN);

	initializeGPIO();

	Serial.begin(9600);
	Serial.println("LCD...");

	while (!Serial);

	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	delay(2000);
	
	t.every(250, UpdateScreen);
	t.every(1000, UpdateTime);

	menu->Navigate(HOME_SCREEN);
}

void UpdateTime() {
	currentTime += 1;
	itoa(currentTime, timeString, 10);
	menu->UpdateTime(timeString);
}

void UpdateScreen() {
	menu->Update();
}

void loop()
{
	t.update();

	//int scanKeyboard = 1;
	//for (int i = 0; scanKeyboard == 1; i += 100) {


	//	if (digitalRead(gpio->ReedSwitch)) {
	//		Serial.print("0");
	//	}
	//	else {
	//		Serial.print("1");
	//		tone(gpio->Piezo, 440, 250);
	//	}

	//	delay(100);

	//	if (i == 1000) {
	//		scanKeyboard = 0;
	//	}
	//}

	/*if (show % 2 == 0) { // Switch relay
		digitalWrite(relayPin, LOW);
	}
	else {
		digitalWrite(relayPin, HIGH);
	}*/
}