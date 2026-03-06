#ifndef _SGK_SGKWINDOW_IMPL_H_
#define _SGK_SGKWINDOW_IMPL_H_

#include "ImplDefinitions.h"
#include "SGK/Window/GraphicWindow.h"
#include "SGK/Window/DebugWindow.h"

#include <Windows.h>

SGK_IMPL_NAMESPACE_BEG

// DebugWindow和GraphicWindow的代理类的基类
class SGKWindow_impl {
private:
	// 不允许复制或创建空白实例
	SGKWindow_impl();
	SGKWindow_impl(SGKWindow_impl&);
	void operator=(SGKWindow_impl&) {};

	WNDCLASS mWndClass;
	HWND mHandle;
	const char* mWndName;
	int mWidth, mHeight, mWidthMax, mHeightMax, mWidthTemp, mHeightTemp;
	unsigned mStartTime;
	bool mStart, mActive, mAllowedMaximized, mMaximized, mCloseRequested, mEnd;

	typedef void (*SGKResizeCallBack)(SGKWindow_impl* window);
	typedef void (*SGKRepaintCallBack)(SGKWindow_impl* window);
protected:
	SGKResizeCallBack mResizeCallback;
	SGKRepaintCallBack mRepaintCallback;

public:
	SGKWindow_impl(HINSTANCE hInst, const char* wndname, WNDPROC wndproc, int width = 800, int height = 600, bool bMaxAllowed = true);
	virtual ~SGKWindow_impl();

	virtual void start(); // 派生窗口务必在自己的start()中首先调用SGK_impl::SGKWindow_impl::start()
	bool isStarted() const;
	void end();
	bool isEnd() const;

	HWND getWindowHandle() const; // 在调用start()后才能获得窗口参数
	void getSize(int* width, int* height) const;
	unsigned getElapsedTime() const;
	bool isActive() const;
	void setActive(bool bActive = true);
	bool isRequestedClose() const;
	void setCloseRequest(bool bClose = true);
	bool isAllowedMaximized() const;
	bool isMaximized() const;
	void setMaximized(bool bMax = true);
	void resize(int width, int height);
	void resizeCallback();
	void repaintCallback();

	virtual void init() = 0;
	virtual void update() = 0;
};

SGK_IMPL_NAMESPACE_END

SGK_NAMESPACE_BEG

// GraphicWindow的代理类
class GraphicWindow::Impl : public SGK_impl::SGKWindow_impl {
private:
	GraphicWindow* mGraphicWindow;

	PIXELFORMATDESCRIPTOR mPfd; HDC mHDC; HGLRC mHRC;

public:
	Impl(HINSTANCE hInst, const char* wndname, WNDPROC wndproc, int width = 800, int height = 600, bool bMaxAllowed = true);
	~Impl();

	void init();
	void update();
};
// DebugWindow的代理类
class DebugWindow::Impl : public SGK_impl::SGKWindow_impl {
private:
	DebugWindow* mDebugWindow;
	bool mWrite;
	int mTop;

public:
	Impl(HINSTANCE hInst, WNDPROC wndproc);
	~Impl();

	bool shouldWrite() const;
	void setWriteFlag(bool flag = false);
	const char* write(const char* buf, Mode mode = Mode::Add);

	int getTopPos() const;
	void setTopPos(int pos);

	void init();
	void update();
};

SGK_NAMESPACE_END

#endif
