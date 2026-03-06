#include "SGK/Input/Manager.h"
#include "InputManager.impl.h"

using namespace SGK::Input;

void Manager::create() { SGK_impl::InputManager_impl::create(); return; }
void Manager::destroy() { SGK_impl::InputManager_impl::destroy(); return; }
Manager Manager::instance() { return Manager(); }

SGK::SGKcharter* Manager::getInputDevices() { return SGK_impl::InputManager_impl::instance()->getInputDevices(); }
void Manager::update() { SGK_impl::InputManager_impl::instance()->update(); return; }
