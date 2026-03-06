#ifndef _SKG_INPUT_MANAGER_IMPL_H_
#define _SGK_INPUT_MANAGER_IMPL_H_

#include "ImplDefinitions.h"
#include "charter.Input.h"

SGK_IMPL_NAMESPACE_BEG

class InputManager_impl : public SGK::NonCopyable {
private:
	InputManager_impl();
	~InputManager_impl();

	bool mEnd;
	SGK::Input::Keyboard::Impl* mKeyboard;

public:
	static void create();
	static void destroy();
	static InputManager_impl* instance();

	SGK::SGKcharter* getInputDevices();
	void update();
};

SGK_IMPL_NAMESPACE_END

#endif
