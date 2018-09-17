// Config.h

#ifndef _CONFIG_h
#define _CONFIG_h

#define I2CADDR_MCP23017 0x20
#define I2CADDR_LCD 0x3F

#define VERSION "2.0.2"

#define KEYPAD_ROW 4
#define KEYPAD_COL 4
#define KEYPAD_BEEP_DURATION 250

#define END_TUNE_DURATION 500

#define LCD_ROW 4
#define LCD_COL 20

#define WELCOME_SCREEN 0
#define HOME_SCREEN 1
#define START_SCREEN 2
#define SETTING_SCREEN 3
#define JOB_SCREEN 4

#define JOB_REFRESH_RATE 10
#define TEMP_REFRESH_RATE_MS 1000

#define DEBUG true

#define WEBSERVER_PORT 80
#define WEBSERVER_SSID "InsoleuseV2"
#define WEBSERVER_PWD "lghs42!$"

#endif

