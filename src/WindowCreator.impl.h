#ifndef _SGK_WINDOWCREATOR_IMPL_H_
#define _SGK_WINDOWCREATOR_IMPL_H_

#include "ImplDefinitions.h"
#include "charter.Window.h"

#include <Windows.h>

SGK_IMPL_NAMESPACE_BEG

// WindowCreator的代理类
class WindowCreator_impl {
private:
	WindowCreator_impl();
	WindowCreator_impl(WindowCreator_impl&);
	void operator=(WindowCreator_impl&) {};

	WindowCreator_impl(HINSTANCE hInst);
	~WindowCreator_impl();
	bool mShouldClose, mEnd;
	HINSTANCE mhInst;
	int mNumDefaultWindows;
	SGKWindow_impl* mSGKWindows[8]; // 6--GraphicWindow, 7--DebugWindow, 0-6--DefaultWindows

public:
	static void create(HINSTANCE hInst);
	static void destroy();
	static WindowCreator_impl* instance();

	SGKWindow_impl* find(HWND hWnd);

	void createGraphicWindow(const char* wndname, int width = 800, int height = 600, bool bMaxAllowed = true);
	void createDebugWindow();
	SGK::SGKcharter* getGraphicWindow();
	SGK::SGKcharter* getDebugWindow();

	void initWindows();
	void updateWindows();
	bool isBusy() const;
	void checkWindowsShouldClose();
	void closeWindowsShouldClose();
	bool isSGKSetToClose() const;
};

SGK_IMPL_NAMESPACE_END

#endif
