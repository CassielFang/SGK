#include "SGKWindow.impl.h"
#include "WindowCreator.impl.h"

#include <Windows.h>

using namespace SGK;

GraphicWindow::GraphicWindow(SGKcharter* charter) : mImpl(0), mCharter(charter), Permitted(charter) {
	invalid_operation(!mCharter->isLocked());
	mCharter->lock();
	SGK_impl::Windowcharter* localcharter = dynamic_cast<SGK_impl::Windowcharter*>(mCharter);
	invalid_operation(localcharter);
	mImpl = dynamic_cast<GraphicWindow::Impl*>(localcharter->mSGKWindow);
	invalid_operation(mImpl);
}
GraphicWindow::~GraphicWindow() {
	mCharter->release();
	delete mCharter;
	mCharter = 0;
}

void GraphicWindow::getSize(int* width, int* height) const { mImpl->getSize(width, height); }
unsigned GraphicWindow::getElapsedTime() const { return mImpl->getElapsedTime(); }
bool GraphicWindow::isActive() const { return mImpl->isActive(); }
bool GraphicWindow::isRequestedClose() const { return mImpl->isRequestedClose(); }
void GraphicWindow::setCloseRequest(bool bClose) { mImpl->setCloseRequest(bClose); }
bool GraphicWindow::isAllowedMaximized() const { return mImpl->isAllowedMaximized(); }
bool GraphicWindow::isMaximized() const { return mImpl->isMaximized(); }


DebugWindow::DebugWindow(SGKcharter* charter) : mImpl(0), mCharter(charter), Permitted(charter) {
	invalid_operation(!mCharter->isLocked());
	mCharter->lock();
	SGK_impl::Windowcharter* localCharter = dynamic_cast<SGK_impl::Windowcharter*>(mCharter);
	invalid_operation(localCharter);
	mImpl = dynamic_cast<DebugWindow::Impl*>(localCharter->mSGKWindow);
	invalid_operation(mImpl);
}
DebugWindow::~DebugWindow() {
	mCharter->release();
	delete mCharter;
	mCharter = 0;
}

void DebugWindow::write(const char* buf, Mode mode) {
	mImpl->write(buf, mode);
	return;
}
