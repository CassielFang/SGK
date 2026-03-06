#ifndef _SGK_WINDOWCREATOR_H_
#define _SGK_WINDOWCREATOR_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 窗口管理类，不建议用户在不知情时自行调用
class WindowCreator {
public:
	static void create(void* hInstance);
	static void destroy();
	// 返回单例类的实例
	static WindowCreator instance();

	// 创建图形窗口
	void createGraphicWindow(const char* wndname, int width = 800, int height = 600, bool bMaxAllowed = true);
	// 创建调试输出窗口
	void createDebugWindow();

	// 获取图形窗口
	SGKcharter* getGraphicWindow();
	// 获取调试输出窗口
	SGKcharter* getDebugWindow();

	// 初始化所有窗口
	void initWindows();
	// 更新所有窗口状态
	void updateWindows();
	// 判断图形窗口是否获得焦点
	bool isBusy() const;
	// 检查是否有窗口需要关闭
	void checkWindowsShouldClose() const;
	// 关闭调用此函数时仍然被标记需要关闭的窗口
	void closeWindowsShouldClose();
	// 通过图形窗口是否关闭了来判断程序主循环是否需要结束
	bool isSGKSetToClose() const;
};

SGK_NAMESPACE_END

#endif
