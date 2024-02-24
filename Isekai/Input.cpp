#include "Input.h"

Input::Input() {

}

Input::Input(const Input &other) {

}

Input::~Input() {

}

void Input::initialize() {
	// Initialize all the keys to being released and not pressed.
	for (int i = 0; i < 256; i++) {
		m_keys[i] = false;
	}
}

void Input::keyDown(unsigned int input) {
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
}

void Input::keyUp(unsigned int input) {
	m_keys[input] = true;
}

bool Input::isKeyDown(unsigned int key) {
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}
