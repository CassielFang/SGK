#ifndef _SKG_INPUT_MANAGER_H_
#define _SGK_INPUT_MANAGER_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Input {

	// 设备输入输出管理
	class Manager {
	public:
		static void create();
		static void destroy();
		// 获取单例类的实例
		static Manager instance();

		// 获取设备，键盘或者鼠标
		SGKcharter* getInputDevices();

		void update();
	};

}

SGK_NAMESPACE_END

#endif
