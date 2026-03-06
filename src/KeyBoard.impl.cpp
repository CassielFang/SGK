#include "Keyboard.impl.h"

#include <Windows.h>

SGK_NAMESPACE_BEG

namespace Input {

	Keyboard::Impl::Impl() : mTurn(false) {
		for (int i = 0; i < 256; ++i) {
			mKeysState[0][i] = mKeysState[1][i] = 0;
		}
	}

	bool Keyboard::Impl::isKeyOn(Keys key) const { return mKeysState[mTurn][static_cast<int>(key)]; }
	bool Keyboard::Impl::isKeyOn(char key) const {
		if (key >= 'A' && key <= 'Z' || key >= '0' && key <= '9') {
			return mKeysState[mTurn][static_cast<int>(key)];
		}
		else if (key >= 'a' && key <= 'z') {
			return mKeysState[mTurn][static_cast<int>(key - 32)];
		}
		else {
			return false;
		}
	}
	bool Keyboard::Impl::isKeyTriggered(Keys key) const {
		return isKeyOn(key) && !mKeysState[!mTurn][static_cast<int>(key)];
	}
	bool Keyboard::Impl::isKeyTriggered(char key) const {
		return isKeyOn(key) && !mKeysState[!mTurn][static_cast<int>(key)];
	}

	void Keyboard::Impl::update() {
		mTurn = !mTurn;
		// strong_assert(GetKeyboardState(mKeysState[static_cast<int>(mTurn)]));
		for (int vkCode = 0; vkCode < 256; ++vkCode) {
			mKeysState[static_cast<int>(mTurn)][vkCode] = GetAsyncKeyState(vkCode) & 0x8000;
		}
		return;
	}

}

SGK_NAMESPACE_END
