#include "Keyboard.impl.h"
#include "InputManager.impl.h"

using namespace SGK;
using namespace SGK::Input;

Keyboard::Keyboard(SGKcharter* charter) : mImpl(nullptr), mCharter(charter), Permitted(charter) {
	invalid_operation(!mCharter->isLocked());
	mCharter->lock();
	SGK_impl::Inputcharter* localcharter = dynamic_cast<SGK_impl::Inputcharter*>(mCharter);
	invalid_operation(localcharter);
	mImpl = localcharter->mKeyboartImpl;
}
Keyboard::~Keyboard() {
	mCharter->release();
	delete mCharter;
	mCharter = nullptr;
}

bool Keyboard::isKeyOn(Keys key) const { return mImpl->isKeyOn(key); }
bool Keyboard::isKeyOn(char key) const { return mImpl->isKeyOn(key); }
bool Keyboard::isKeyTriggered(Keys key) const { return mImpl->isKeyTriggered(key); }
bool Keyboard::isKeyTriggered(char key) const { return mImpl->isKeyTriggered(key); }
