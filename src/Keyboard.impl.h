#ifndef _SGK_INPUT_KEYBOARD_IMPL_H_
#define _SGK_INPUT_KEYBOARD_IMPL_H_

#include "ImplDefinitions.h"
#include "SGK/Input/Keyboard.h"

SGK_NAMESPACE_BEG

namespace Input {

	class Keyboard::Impl : public NonCopyable {
	private:
		bool mKeysState[2][256];
		bool mTurn;
		
	public:
		Impl();

		bool isKeyOn(Keys key) const;
		bool isKeyOn(char key) const;
		bool isKeyTriggered(Keys key) const;
		bool isKeyTriggered(char key) const;

		void update();
	};

}

SGK_NAMESPACE_END

#endif
