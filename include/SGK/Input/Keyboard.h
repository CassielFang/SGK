#ifndef _SGK_INPUT_KEYBOARD_H_
#define _SGK_INPUT_KEYBOARD_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Input {

	// 键盘设备
	class Keyboard : public Permitted {
	public:
		Keyboard(SGKcharter* charter);
		~Keyboard();

		// 定义特殊按键
		enum class Keys {
			KB_SHIFT = 0x10, KB_CONTROL, KB_ALT,
			KB_ESCAPE = 0x20,
			KB_LEFT = 0x25, KB_UP, KB_RIGHT, KB_DOWN,
			KB_NUMPAD0 = 0x60, KB_NUMPAD1, KB_NUMPAD2, KB_NUMPAD3, KB_NUMPAD4,
			KB_NUMPAD5, KB_NUMPAD6, KB_NUMPAD7, KB_NUMPAD8, KB_NUMPAD9,
			KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, KB_F6, KB_F7, KB_F8, KB_F9, KB_F10, KB_F11, KB_F12
		};

		// 检测按键是否按下
		bool isKeyOn(Keys key) const;
		// 检测按键是否按下，用于字母键（大写）、数字键
		bool isKeyOn(char key) const;
		// 检测按键是否第一次被按下
		bool isKeyTriggered(Keys key) const;
		// 检测按键是否第一次被按下，用于字母键（大写）、数字键
		bool isKeyTriggered(char key) const;

		class Impl;
	private:
		Impl* mImpl;
		SGKcharter* mCharter;
	};

}

SGK_NAMESPACE_END

#endif
