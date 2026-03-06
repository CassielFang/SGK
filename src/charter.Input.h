#ifndef _SGK_CHARTER_INPUT_H_
#define _SGK_CHARTER_INPUT_H_

#include "ImplDefinitions.h"
#include "Keyboard.impl.h"

SGK_IMPL_NAMESPACE_BEG

class Inputcharter : public SGK::SGKcharter {
public:
	Inputcharter() = delete;
	Inputcharter(SGK::Input::Keyboard::Impl* keyboartImpl) : mKeyboartImpl(keyboartImpl) {}
	SGK::Input::Keyboard::Impl* mKeyboartImpl;
};

SGK_IMPL_NAMESPACE_END

#endif
