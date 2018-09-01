// 
// 
// 

#include "Keyboard.h"
#include <Keypad.h>
#include <Keypad_MC17.h>

void Keyboard::Init() {
	this->keypad->begin();
}

char Keyboard::GetKey() {
	return this->keypad->getKey();
}