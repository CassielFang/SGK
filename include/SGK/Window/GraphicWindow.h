#ifndef _SGK_GRAPHICWINDOW_H_
#define _SGK_GRAPHICWINDOW_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 图形窗口，所有绘制操作呈现于此
class GraphicWindow : public Permitted {
public:
	GraphicWindow(SGKcharter* charter);
	~GraphicWindow();

	// 获取窗口大小（只有全屏和固定大小的非全屏两种尺寸
	void getSize(int* width, int* height) const;
	// 获取自该窗口创建开始后的运行时间（毫秒）
	unsigned getElapsedTime() const;
	// 是否置于最顶层（具有焦点）
	bool isActive() const;
	// 是否发出了关闭图形窗口的请求（点击右上角关闭或者非全屏时按下ESC）
	bool isRequestedClose() const;
	// 设置关闭信号
	void setCloseRequest(bool bClose = true);
	// 是否允许全屏
	bool isAllowedMaximized() const;
	// 是否是全屏状态
	bool isMaximized() const;

	// 在GraphicWindow外实现，主循环开始前执行一次
	void init();
	// 在GraphicWindow外实现，主循环中每次都执行
	void update();

	class Impl;
private:
	Impl* mImpl;
	SGKcharter* mCharter;
};

SGK_NAMESPACE_END

#endif
