# UVPlatesetter
Code and doc about UV Platesetter V2

# DevEnv
I develop with Visual Studio Community 2017 (free) and the extension Visual Micro that give a nice debugging experience. (shareware, 90 days trial, https://www.visualmicro.com/)

You can use the classical Arduino IDE to compile the code too.

You'll need to install USB drivers in order to communicate with the Lolin Node MCU v3 : https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

You'll need to install this module for the Arduino IDE and Visual Micro in order to program the board: https://github.com/esp8266/Arduino

Diagrams are made with KiCad (free and open source, http://kicad-pcb.org/download/)

# External Library 
I use the following libraries for the code:
 - Wire
 - Keypad and Keypad MC17 (https://github.com/joeyoung/arduino_keypads/)
 - LiquidCrystal
 
 I use the following library for Kicad:
  - Node MCU : https://github.com/MarginallyClever/kicad-ESP8266
  - MCP23017 : https://github.com/mikepurvis/kicad-library-foo/blob/master/MCP23017.lib
