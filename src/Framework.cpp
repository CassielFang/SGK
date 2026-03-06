#include "ImplDefinitions.h"
#include "SGK/Framework.h"
#include "SGK/Window/WindowCreator.h"
#include "SGK/Window/GraphicWindow.h"
#include "SGK/Input/Manager.h"
#include "SGK/Threading/Thread.h"
#include "SGK/FileGovernor/FileIO.h"
#include "SGK/Graphics/Core.h"
#include <sstream>

#include <Windows.h>

SGK_IMPL_NAMESPACE_BEG

class FrameRateController : public SGK::NonCopyable {
public:
    FrameRateController(int frameRate) : mTargetRate(frameRate), m10offset(0), mC(0), mPause(0) {
        mTargetInterval = 1000 / frameRate;
        m10TargetInterval = 10000 / frameRate;
        if (m10TargetInterval > mTargetInterval * 10) { mC = 1; }
        else if (m10TargetInterval < mTargetInterval * 10) { mC = -1; }
        mLastFrameInterval = mNowFrameInterval = mNowSample = 0;
        mLastSample = SGKClock::instance()->getGlobalTime();
    }

    void control() {
        mNowSample = SGKClock::instance()->getGlobalTime();
        mNowFrameInterval = mNowSample - mLastSample;
        mLastSample = mNowSample;
        m10offset += mNowFrameInterval * 10 - m10TargetInterval;
        if (m10offset <= 5 && m10offset >= -5) {
            SGK::Thread::sleep(mTargetInterval);
        }
        else if (m10offset <= 15 && m10offset >= -15) {
            SGK::Thread::sleep(mTargetInterval + mC);
            m10offset = 0;
        }
        else {
            mPause = mTargetInterval - m10offset / 10;
            if (mPause > 0) {
                SGK::Thread::sleep(mPause);
            }
            else {
                SGK::Thread::sleep(0);
            }
        }
        if (m10offset > 5000 || m10offset < -5000) {
            m10offset = 0;
        }
    }
    
private:
    int mTargetRate, mTargetInterval, m10TargetInterval, m10offset, mC, mPause;
    unsigned mLastFrameInterval, mNowFrameInterval, mLastSample, mNowSample;
}* gFrameRateController;

SGK_IMPL_NAMESPACE_END

SGK_NAMESPACE_BEG

static GraphicWindow* gGraphicWindow = 0;

Framework Framework::instance() { return Framework(); }

void Framework::getSize(int* width, int* height) const { gGraphicWindow->getSize(width, height); return; }
unsigned Framework::getElapsedTime() const { return gGraphicWindow->getElapsedTime(); }
bool Framework::isActive() const { return gGraphicWindow->isActive(); }
bool Framework::isRequestedClose() const { return gGraphicWindow->isRequestedClose(); }
void Framework::setCloseRequest(bool bClose) { gGraphicWindow->setCloseRequest(bClose); }
bool Framework::isAllowedMaximized() const { return gGraphicWindow->isAllowedMaximized(); }
bool Framework::isMaximized() const { return gGraphicWindow->isMaximized(); }

void GraphicWindow::init() {
    SGK_impl::gFrameRateController = new SGK_impl::FrameRateController(60);
    gGraphicWindow = new GraphicWindow(WindowCreator::instance().getGraphicWindow());
    Framework().init();
    return;
}
void GraphicWindow::update() {
    SGK_impl::gFrameRateController->control();
    Framework().update();
    if (gGraphicWindow->isRequestedClose()) {
        delete gGraphicWindow;
        gGraphicWindow = nullptr;
    }
    return;
}

SGK_NAMESPACE_END

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    MSG msg = {};
    
try {
    SGK_impl::SGKClock::create();
    SGK::WindowCreator::create(hInstance);
    SGK::Input::Manager::create();
    SGK::FileIO::create();
    SGK::Graphics::Core::create();

    SGK::WindowCreator wndCreator = SGK::WindowCreator::instance();
    wndCreator.createDebugWindow();
    wndCreator.createGraphicWindow("SGK Graphic Window", 800, 600, true);

    SGK::Input::Manager inputManager = SGK::Input::Manager::instance();

    wndCreator.initWindows();

    SGK::FileIO fileIO = SGK::FileIO::instance();

    while (!wndCreator.isSGKSetToClose()) {
        if (wndCreator.isBusy()) {
            if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            inputManager.update();
            wndCreator.checkWindowsShouldClose();
            wndCreator.updateWindows();
        }
        else {
            if (GetMessage(&msg, 0, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        wndCreator.closeWindowsShouldClose();
        fileIO.update();
    }

    SGK::Graphics::Core::destroy();
    SGK::FileIO::destroy();
    SGK::Input::Manager::destroy();
    SGK::WindowCreator::destroy();
    SGK_impl::SGKClock::destroy();
}
    catch (SGK_impl::Exception_assert& e) {
        std::stringstream ss;
        ss << "Assert exception (" << e.getInfo_file() << " : " << e.getInfo_line() << "): " << e.getMessage();
        OutputDebugString(ss.str().c_str());
        MessageBox(0, ss.str().c_str(), "Error!", MB_ICONERROR | MB_OK);
    }
    catch (...) {
        OutputDebugString("Unknown erro");
        MessageBox(0, "Unknown erro", "Error!", MB_ICONERROR | MB_OK);
    }
    return 0;
}
