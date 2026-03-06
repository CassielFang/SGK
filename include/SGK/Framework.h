#ifndef _SGK_FRAMEWORK_H_
#define _SGK_FRAMEWORK_H_

#include "Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 架构模块，支持一些基础功能，内部运行SGK所有的主要功能模块
class Framework {
public:
	static Framework instance();

	void getSize(int* width, int* height) const;
	// 获取自该窗口创建开始后的运行时间（毫秒）
	unsigned getElapsedTime() const;
	// 是否置于最顶层
	bool isActive() const;
	bool isRequestedClose() const;
	void setCloseRequest(bool bClose = true);
	bool isAllowedMaximized() const;
	bool isMaximized() const;

	void init();
	void update();
};

SGK_NAMESPACE_END

#endif
