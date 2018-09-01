/*
 Name:		Insoleuse.ino
 Created:	9/1/2018 5:21:38 PM
 Author:	istac
*/

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Keypad.h>
#include <Keypad_MC17.h>

#define I2CADDR_MCP23017 0x20
#define I2CADDR_LCD 0x3F

LiquidCrystal_PCF8574 lcd(I2CADDR_LCD);

int show;
int relayPin = D8;
int piezoPin = D5;
int reedSwitchPin = D6;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = { 4, 5, 6, 7 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 0, 1, 2, 3 }; //connect to the column pinouts of the keypad

Keypad_MC17 keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR_MCP23017);

void setup()
{
	keypad.begin();

	Serial.begin(9600);
	Serial.println("LCD...");

	while (!Serial);

	Wire.begin();
	Wire.beginTransmission(0x3F);
	Wire.endTransmission();
	lcd.begin(20, 4); // initialize the lcd
	show = 0;

	pinMode(relayPin, OUTPUT);
	pinMode(piezoPin, OUTPUT);
	pinMode(reedSwitchPin, INPUT);
}

void loop()
{
	int scanKeyboard = 1;
	for (int i = 0; scanKeyboard == 1; i += 100) {
		char key = keypad.getKey();
		if (key) {
			Serial.println(key);
		}
		if (digitalRead(reedSwitchPin)) {
			Serial.print("0");
		}
		else {
			Serial.print("1");
		}
		delay(100);
		if (i == 1000) {
			scanKeyboard = 0;
		}
	}

	if (show % 2 == 0) {
		digitalWrite(relayPin, LOW);
		tone(piezoPin, 440);
	}
	else {
		digitalWrite(relayPin, HIGH);
		noTone(piezoPin);
	}


	if (show == 0) {
		lcd.setBacklight(255);
		lcd.home(); lcd.clear();
		lcd.print("Hello LCD");

		lcd.setBacklight(0);
		delay(400);
		lcd.setBacklight(255);

	}
	else if (show == 1) {
		lcd.clear();
		lcd.print("Cursor On");
		lcd.cursor();

	}
	else if (show == 2) {
		lcd.clear();
		lcd.print("Cursor Blink");
		lcd.blink();

	}
	else if (show == 3) {
		lcd.clear();
		lcd.print("Cursor OFF");
		lcd.noBlink();
		lcd.noCursor();

	}
	else if (show == 4) {
		lcd.clear();
		lcd.print("Display Off");
		lcd.noDisplay();

	}
	else if (show == 5) {
		lcd.clear();
		lcd.print("Display On");
		lcd.display();

	}
	else if (show == 7) {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("*** first line.");
		lcd.setCursor(0, 1);
		lcd.print("*** second line.");

	}
	else if (show == 8) {
		lcd.scrollDisplayLeft();
	}
	else if (show == 9) {
		lcd.scrollDisplayLeft();
	}
	else if (show == 10) {
		lcd.scrollDisplayLeft();
	}
	else if (show == 11) {
		lcd.scrollDisplayRight();
	}
	show = (show + 1) % 12;
}