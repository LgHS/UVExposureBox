// Keyboard.h

#ifndef _KEYBOARD_h
#define _KEYBOARD_h

#include <Keypad_MC17.h>
#include "Config.h"

class Keyboard {
public:
	void Init();
	char GetKey();

private:
	char keys[KEYPAD_ROW][KEYPAD_COL] = {
		  {'1','2','3', 'A'},
		  {'4','5','6', 'B'},
		  {'7','8','9', 'C'},
		  {'*','0','#', 'D'}
	};

	byte rowPins[KEYPAD_ROW] = { 4, 5, 6, 7 };
	byte colPins[KEYPAD_COL] = { 0, 1, 2, 3 };

	Keypad_MC17* keypad = new Keypad_MC17(makeKeymap(keys), rowPins, colPins, KEYPAD_ROW, KEYPAD_COL, I2CADDR_MCP23017);
};

#endif

