#include "InputManager.impl.h"

using namespace SGK_impl;

static InputManager_impl* gInputManager = nullptr;

InputManager_impl::InputManager_impl() : mEnd(false) {
	invalid_operation(!gInputManager);
	mKeyboard = new SGK::Input::Keyboard::Impl;
}
InputManager_impl::~InputManager_impl() {
	invalid_operation(mEnd);
	delete mKeyboard;
	mKeyboard = nullptr;
}

void InputManager_impl::create() { gInputManager = new InputManager_impl; }
void InputManager_impl::destroy() {
	gInputManager->mEnd = true;
	delete gInputManager;
	gInputManager = nullptr;
}
InputManager_impl* InputManager_impl::instance() { return gInputManager; }

SGK::SGKcharter* InputManager_impl::getInputDevices() {
	return new Inputcharter(mKeyboard);
}
void InputManager_impl::update() {
	mKeyboard->update();
	return;
}
