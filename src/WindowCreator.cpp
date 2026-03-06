#include "SGK/Window/WindowCreator.h"
#include "WindowCreator.impl.h"

using namespace SGK;

void WindowCreator::create(void* hInstance) {
	HINSTANCE hInst = reinterpret_cast<HINSTANCE>(hInstance);
	invalid_operation(hInst);
	SGK_impl::WindowCreator_impl::create(hInst);
	return;
}
void WindowCreator::destroy() { SGK_impl::WindowCreator_impl::destroy(); return; }
WindowCreator WindowCreator::instance() { return WindowCreator(); }

void WindowCreator::createGraphicWindow(const char* wndname, int width, int height, bool bMaxAllowed) {
	SGK_impl::WindowCreator_impl::instance()->createGraphicWindow(wndname, width, height, bMaxAllowed);
	return;
}
void WindowCreator::createDebugWindow() {
	SGK_impl::WindowCreator_impl::instance()->createDebugWindow();
	return;
}

SGKcharter* WindowCreator::getGraphicWindow() { return SGK_impl::WindowCreator_impl::instance()->getGraphicWindow(); }
SGKcharter* WindowCreator::getDebugWindow() { return SGK_impl::WindowCreator_impl::instance()->getDebugWindow(); }

void WindowCreator::initWindows() { SGK_impl::WindowCreator_impl::instance()->initWindows(); return; }
void WindowCreator::updateWindows() { SGK_impl::WindowCreator_impl::instance()->updateWindows(); return; }
bool WindowCreator::isBusy() const { return SGK_impl::WindowCreator_impl::instance()->isBusy(); }
void WindowCreator::checkWindowsShouldClose() const { SGK_impl::WindowCreator_impl::instance()->checkWindowsShouldClose(); return; }
void WindowCreator::closeWindowsShouldClose() { SGK_impl::WindowCreator_impl::instance()->closeWindowsShouldClose(); return; }
bool WindowCreator::isSGKSetToClose() const { return SGK_impl::WindowCreator_impl::instance()->isSGKSetToClose(); }
