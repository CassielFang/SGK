#include "WindowCreator.impl.h"

using namespace SGK_impl;

static WindowCreator_impl* gWindowCreator = nullptr;

static LRESULT CALLBACK SGKWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	SGKWindow_impl* sgkwnd = gWindowCreator->find(hWnd);
	switch (uMsg) {
	case WM_SYSCOMMAND:
		switch (wParam & 0xfff0) {
		case SC_MAXIMIZE:
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
			break;
		case SC_RESTORE:
			DefWindowProc(hWnd, uMsg, wParam, lParam);
			if (sgkwnd->isAllowedMaximized()) {
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX);
			}
			else {
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
			}
			break;
		default: break;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			if (sgkwnd->isMaximized()) {
				SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			}
			else {
				sgkwnd->setCloseRequest();
			}
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	case WM_ACTIVATE:
		switch (wParam) {
		case WA_ACTIVE: case WA_CLICKACTIVE:
			sgkwnd->setActive(true);
			break;
		default:
			sgkwnd->setActive(false);
			break;
		}
		break;
	case WM_SIZE:
		sgkwnd->setMaximized(wParam == SIZE_MAXIMIZED);
		sgkwnd->resize(LOWORD(lParam), HIWORD(lParam));
		sgkwnd->resizeCallback();
		break;
	case WM_PAINT:
		sgkwnd->repaintCallback();
		break;
	case WM_CLOSE:
		sgkwnd->setCloseRequest();
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

WindowCreator_impl::WindowCreator_impl(HINSTANCE hInst) : mShouldClose(false), mEnd(false),
	mhInst(hInst), mNumDefaultWindows(0) {
	invalid_operation(!gWindowCreator);
	for (int i = 0; i < 8; ++i) {
		mSGKWindows[i] = 0;
	}
}
WindowCreator_impl::~WindowCreator_impl() { invalid_operation(mEnd); }

void WindowCreator_impl::create(HINSTANCE hInst) {
	gWindowCreator = new WindowCreator_impl(hInst);
	return;
}
void WindowCreator_impl::destroy() {
	gWindowCreator->mEnd = true;
	delete gWindowCreator;
	gWindowCreator = nullptr;
	return;
}
WindowCreator_impl* WindowCreator_impl::instance() { return gWindowCreator; }

SGKWindow_impl* WindowCreator_impl::find(HWND hWnd) {
	for (int i = 0; i < 8; ++i) {
		if (mSGKWindows[i] == 0) { continue; }
		if (mSGKWindows[i]->getWindowHandle() == hWnd) {
			return mSGKWindows[i];
		}
	}
	return 0;
}

void WindowCreator_impl::createGraphicWindow(const char* wndname, int width, int height, bool bMaxAllowed) {
	mSGKWindows[6] = new SGK::GraphicWindow::Impl(mhInst, wndname, SGKWndProc, width, height, bMaxAllowed);
	mSGKWindows[6]->start();
	invalid_operation(mSGKWindows[6]->isStarted());
	return;
}
void WindowCreator_impl::createDebugWindow() {
	mSGKWindows[7] = new SGK::DebugWindow::Impl(mhInst, SGKWndProc);
	mSGKWindows[7]->start();
	invalid_operation(mSGKWindows[7]->isStarted());
	return;
}
SGK::SGKcharter* WindowCreator_impl::getGraphicWindow() {
	return new Windowcharter(mSGKWindows[6]);
}
SGK::SGKcharter* WindowCreator_impl::getDebugWindow() {
	return new Windowcharter(mSGKWindows[7]);
}

void WindowCreator_impl::initWindows() {
	mSGKWindows[7]->init();
	mSGKWindows[7]->update();
	mSGKWindows[6]->init();
	if (mNumDefaultWindows == 0) {
		return;
	}
	int count = 0;
	for (int i = 0; i < 6; ++i) {
		if (mSGKWindows[i]) {
			mSGKWindows[i]->init();
			++count;
			if (count >= mNumDefaultWindows) {
				break;
			}
		}
	}
	return;
}
void WindowCreator_impl::updateWindows() {
	mSGKWindows[7]->update();
	mSGKWindows[6]->update();
	if (mNumDefaultWindows > 0) {
		int count = 0;
		for (int i = 0; i < 6; ++i) {
			if (mSGKWindows[i]) {
				mSGKWindows[i]->update();
				++count;
				if (count >= mNumDefaultWindows) {
					break;
				}
			}
		}
	}
	return;
}
bool WindowCreator_impl::isBusy() const { return mSGKWindows[6]->isActive(); }
void WindowCreator_impl::checkWindowsShouldClose() {
	if (mSGKWindows[6]->isRequestedClose()) {
		mSGKWindows[7]->setCloseRequest();
		if (mNumDefaultWindows > 0) {
			int count = 0;
			for (int i = 0; i < 6; ++i) {
				if (mSGKWindows[i]) {
					mSGKWindows[i]->setCloseRequest();
					++count;
					if (count >= mNumDefaultWindows) {
						break;
					}
				}
			}
		}
	}
	if (mSGKWindows[7]->isRequestedClose()) {
		if (mSGKWindows[6]) {
			mSGKWindows[7]->setCloseRequest(false);
		}
	}
	return;
}
void WindowCreator_impl::closeWindowsShouldClose() {
	if (mSGKWindows[6]->isRequestedClose()) {
		mShouldClose = true;
		delete mSGKWindows[6];
		mSGKWindows[6] = 0;
	}
	if (mSGKWindows[7]->isRequestedClose()) {
		mSGKWindows[7]->setCloseRequest(false);
	}
	if (mNumDefaultWindows > 0) {
		int count = 0;
		for (int i = 0; i < 6; ++i) {
			if (mSGKWindows[i]) {
				delete mSGKWindows[i];
				mSGKWindows[i] = 0;
				++count;
				if (count >= mNumDefaultWindows) {
					break;
				}
			}
		}
	}
	return;
}
bool WindowCreator_impl::isSGKSetToClose() const { return mShouldClose; }
