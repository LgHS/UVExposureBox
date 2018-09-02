// Config.h

#ifndef _CONFIG_h
#define _CONFIG_h

#include "arduino.h"

#define I2CADDR_MCP23017 0x20
#define I2CADDR_LCD 0x3F
#define VERSION "2.0.1"
#define KEYPAD_ROW 4
#define KEYPAD_COL 4
#define LCD_ROW 4
#define LCD_COL 20

struct GPIO {
	int Relay = D8;
	int Piezo = D7;
	int ReedSwitch = D6;
};

#endif

