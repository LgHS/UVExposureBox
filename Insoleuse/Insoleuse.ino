/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/

#include "Keyboard.h"
#include "Menu.h"
#include <Wire.h>
#include "Config.h"

Keyboard* keyboard = new Keyboard();
ApplicationMenu* menu = new ApplicationMenu();
GPIO* gpio = new GPIO();

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

	keyboard->Init();

	Serial.begin(9600);
	Serial.println("LCD...");

	while (!Serial);

	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();

	delay(2000);
}

void loop()
{
	menu->Navigate(HOME_SCREEN);

	int scanKeyboard = 1;
	for (int i = 0; scanKeyboard == 1; i += 100) {
		char key = keyboard->GetKey();

		if (key) {
			Serial.println(key);
			tone(gpio->Piezo, 440, 250);
		}

		if (digitalRead(gpio->ReedSwitch)) {
			Serial.print("0");
		}
		else {
			Serial.print("1");
			tone(gpio->Piezo, 440, 250);
		}

		delay(100);

		if (i == 1000) {
			scanKeyboard = 0;
		}
	}

	/*if (show % 2 == 0) { // Switch relay
		digitalWrite(relayPin, LOW);
	}
	else {
		digitalWrite(relayPin, HIGH);
	}*/
}