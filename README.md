# UV Exposure Box
Code and doc about UV Exposure Box v2.0.2

# DevEnv
I develop with Visual Studio Community 2017 (free) and the extension Visual Micro that give a nice debugging experience. (shareware, 90 days trial, https://www.visualmicro.com/)

You can use the classical Arduino IDE to compile the code too.

You'll need to install USB drivers in order to communicate with the Lolin Node MCU v3 : https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

You'll need to install this module for the Arduino IDE and Visual Micro in order to program the board: https://github.com/esp8266/Arduino

Diagrams are made with KiCad (free and open source, http://kicad-pcb.org/download/)

To upload files to rom I use this tool: https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.1.3/ESP8266FS-0.1.3.zip, for more information about how to install and use it to read this article: https://circuits4you.com/2018/01/31/upload-image-png-jpeg-to-esp8266-web-page/

# Web Portal Screenshot

![alt text](https://github.com/LgHS/UVPlatesetter/blob/master/img/screen.PNG)

# External Tool

 - ESP8266 exception decoder: https://github.com/me-no-dev/EspExceptionDecoder
 - ESP8266 exception decoder CLI: https://github.com/littleyoda/EspStackTraceDecoder
 - SPIFFS upload tool: https://github.com/esp8266/arduino-esp8266fs-plugin

# External Library 
I use the following libraries for the code:
 - Wire
 - Keypad and Keypad MC17 (https://github.com/joeyoung/arduino_keypads/)
 - LiquidCrystal_I2C
 - I've written a fork of LiquidMenu that add global functions to screens for easier navigation, I don't have to mess with lines, lines pointers and focus to execute binded UI logic, the code is included with the sources.
 - Timer Library for Arduino (https://github.com/JChristensen/Timer)
 
 I use the following library for Kicad:
  - Node MCU : https://github.com/MarginallyClever/kicad-ESP8266
  - MCP23017 : https://github.com/mikepurvis/kicad-library-foo/blob/master/MCP23017.lib
  
  # Support
Brewed with love in belgium - Under MIT Licence

Support : istace.emmanuel@hotmail.com | eis on RocketChat:chat.lghs.be | Manu404 on irc:freenode:#lghs

