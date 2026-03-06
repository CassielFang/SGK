#include "SGKWindow.impl.h"
#include "SGK/Window/WindowCreator.h"
#include "SGK/Threading/Thread.h"

#include "glad.h"
#pragma comment(lib, "opengl32.lib")

#include <string>

SGK_IMPL_NAMESPACE_BEG

SGKWindow_impl::SGKWindow_impl(HINSTANCE hInst, const char* wndname, WNDPROC wndproc, int width, int height, bool bMaxAllowed) :
	mWndClass(), mHandle(0), mWndName(wndname), mWidth(width), mHeight(height),
	mWidthMax(0), mHeightMax(0), mWidthTemp(0), mHeightTemp(0), mStartTime(0),
	mStart(false), mActive(false), mAllowedMaximized(bMaxAllowed), mMaximized(false), mCloseRequested(false), mEnd(false),
	mResizeCallback(0), mRepaintCallback(0) {
	mWndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	mWndClass.cbClsExtra = mWndClass.cbWndExtra = 0;
	mWndClass.hbrBackground = 0;
	mWndClass.hInstance = hInst;
	mWndClass.lpszClassName = mWndName;
	mWndClass.lpfnWndProc = wndproc;
	assertEx(RegisterClass(&mWndClass), "Failed to register the window class!");
}
SGKWindow_impl::~SGKWindow_impl() {
	strong_assert(mCloseRequested);
	DestroyWindow(mHandle);
	UnregisterClass(mWndClass.lpszClassName, mWndClass.hInstance);
}

void SGKWindow_impl::start() {
	mStartTime = SGK_impl::SGKClock::instance()->getGlobalTime();
	RECT rc = {};
	SetRect(&rc, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT + mWidth, CW_USEDEFAULT + mHeight);
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX, false);
	int style = mAllowedMaximized ? (WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX) : (WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
	mHandle = CreateWindow(mWndClass.lpszClassName, mWndName, style,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, 0, 0, mWndClass.hInstance, 0);
	assertEx(mHandle, "Failed to create the window");
	ShowWindow(mHandle, SW_SHOW);
	mStart = true;
	return;
}
bool SGKWindow_impl::isStarted() const { return mStart; }
void SGKWindow_impl::end() { mEnd = true; return; }
bool SGKWindow_impl::isEnd() const { return mEnd; }

HWND SGKWindow_impl::getWindowHandle() const { return mHandle; }
void SGKWindow_impl::getSize(int* width, int* height) const {
	if (isMaximized()) {
		if (width) { *width = mWidthMax; }
		if (height) { *height = mHeightMax; }
	}
	else { 
		if (width) { *width = mWidth; }
		if (height) { *height = mHeight; }
	}
	return;
}
unsigned SGKWindow_impl::getElapsedTime() const {
	unsigned tmNow = SGK_impl::SGKClock::instance()->getGlobalTime();
	return tmNow - mStartTime;
}
bool SGKWindow_impl::isActive() const { return mActive; }
void SGKWindow_impl::setActive(bool bActive) { mActive = bActive; return; }
bool SGKWindow_impl::isRequestedClose() const { return mCloseRequested; }
void SGKWindow_impl::setCloseRequest(bool bClose) { mCloseRequested = bClose; return; }
bool SGKWindow_impl::isAllowedMaximized() const { return mAllowedMaximized; }
bool SGKWindow_impl::isMaximized() const { return mMaximized; }
void SGKWindow_impl::setMaximized(bool bMax) { mMaximized = bMax; return; }
void SGKWindow_impl::resize(int width, int height) {
	if (!mWidthTemp) { mWidthTemp = width; mHeightTemp = height; }
	else if (!mWidthMax) { mWidthMax = width; mHeightMax = height; }
	return;
}
void SGKWindow_impl::resizeCallback() {
	if (isStarted() && mResizeCallback) {
		mResizeCallback(this);
	}
	return;
}
void SGKWindow_impl::repaintCallback() {
	if (isStarted() && mRepaintCallback) {
		mRepaintCallback(this);
	}
	return;
}

SGK_IMPL_NAMESPACE_END

using namespace SGK;

static void GraphicResizeCallback(SGK_impl::SGKWindow_impl* window) {
	int width, height;
	window->getSize(&width, &height);
	glViewport(0, 0, width, height);
	GraphicWindow wnd = WindowCreator::instance().getGraphicWindow();
	return;
}
GraphicWindow::Impl::Impl(HINSTANCE hInst, const char* wndname, WNDPROC wndproc, int width, int height, bool bMaxAllowed) :
	SGKWindow_impl(hInst, wndname, wndproc, width, height, bMaxAllowed), mGraphicWindow(0),
	mPfd(), mHDC(), mHRC() {
	mResizeCallback = GraphicResizeCallback;
}
GraphicWindow::Impl::~Impl() {
	delete mGraphicWindow;
	mGraphicWindow = 0;
}

void GraphicWindow::Impl::init() {
	mHDC = GetDC(getWindowHandle());
	mPfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	mPfd.nVersion = 1;
	mPfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	mPfd.iPixelType = PFD_TYPE_RGBA;
	mPfd.cColorBits = 24;
	mPfd.cAlphaBits = 16;
	mPfd.iLayerType = PFD_MAIN_PLANE;
	SetPixelFormat(mHDC, ChoosePixelFormat(mHDC, &mPfd), &mPfd);
	mHRC = wglCreateContext(mHDC);
	assertEx(mHRC, "Failed to create OpenGL context!");
	assertEx(wglMakeCurrent(mHDC, mHRC), "Failed to create OpenGL current!");
	assertEx(gladLoadGL(), "Failed to load all OpenGL function pointers!");
	
	int width, height;
	getSize(&width, &height);
	glViewport(0, 0, width, height);

	mGraphicWindow = new GraphicWindow(WindowCreator::instance().getGraphicWindow());
	mGraphicWindow->init();
	return;
}
void GraphicWindow::Impl::update() {
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mGraphicWindow->update();
	SwapBuffers(mHDC);
	return;
}


namespace {
	static std::string gDebugOutBuf;
	static unsigned gDebugFrameNum = UINT_MAX;
	static char gFrameNumber[10];
}
static void DebugRepaintCallback(SGK_impl::SGKWindow_impl* window) {
	DebugWindow::Impl* wnd = dynamic_cast<DebugWindow::Impl*>(window);
	invalid_operation(wnd);
	if (!wnd->shouldWrite()) {
		return;
	}
	int h;
	wnd->getSize(0, &h);
	const char* buf = wnd->write(0, SGK::DebugWindow::Mode::Return);
	HWND hWnd = wnd->getWindowHandle();
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	RECT rect;
	GetClientRect(hWnd, &rect);
	FillRect(hDC, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"font");
	SelectObject(hDC, hFont);
	SetBkMode(hDC, OPAQUE);
	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(255, 255, 255));

	int line = 0, p = 0;
	while (buf[p] != '\0' && p < static_cast<int>(strlen(buf))) {
		if (buf[p] == '\n') {
			++line;
		}
		++p;
	}
	if (wnd->getTopPos() + line * 20 > h) {
		wnd->setTopPos(h - line * 20);
	}
	line = 0;
	p = 0;
	for (int head = 0; p < static_cast<int>(strlen(buf)); ++p) {
		if (buf[p] == '\0') {
			break;
		}
		else if (buf[p] == '\n') {
			TextOut(hDC, 0, wnd->getTopPos() + line*20, buf + head, p - head);
			++line;
			head = p + 1;
		}
	}

	DeleteObject(hFont);
	EndPaint(hWnd, &ps);
	return;
}
DebugWindow::Impl::Impl(HINSTANCE hInst, WNDPROC wndproc) :
	SGKWindow_impl(hInst, "SGK Debug Window", wndproc, 600, 400, false), mDebugWindow(0),
	mWrite(true), mTop(0) {
	mRepaintCallback = DebugRepaintCallback;
}
DebugWindow::Impl::~Impl() {
	delete mDebugWindow;
	mDebugWindow = 0;
}

bool DebugWindow::Impl::shouldWrite() const { return mWrite; }
void DebugWindow::Impl::setWriteFlag(bool flag) { mWrite = flag; return; }
const char* DebugWindow::Impl::write(const char* buf, Mode mode) {
	if (!shouldWrite()) {
		unsigned frameNumber = gDebugFrameNum;
		gDebugOutBuf += "<Frame ";
		for (int i = 0; i < 10; ++i) {
			gFrameNumber[i] = '0';
		}
		int digit = 0;
		do {
			gFrameNumber[digit] = frameNumber % 10 + '0';
			frameNumber /= 10;
			++digit;
		} while (frameNumber != 0);
		--digit;
		for (; digit >= 0; --digit) {
			gDebugOutBuf += gFrameNumber[digit];
		}
		gDebugOutBuf += "> ";
	}
	switch (mode) {
	case Mode::Add:
		gDebugOutBuf += buf;
		break;
	case Mode::Cover:
		gDebugOutBuf = buf;
		write("", Mode::Add);
		break;
	case Mode::Return:
		return gDebugOutBuf.c_str();
		break;
	default: break;
	}
	setWriteFlag(true);
	return gDebugOutBuf.c_str();
}

int DebugWindow::Impl::getTopPos() const { return mTop; }
void DebugWindow::Impl::setTopPos(int pos) { mTop = pos; return; }

void DebugWindow::Impl::init() {
	gDebugOutBuf = "";
	mDebugWindow = new DebugWindow(WindowCreator::instance().getDebugWindow());
	gDebugFrameNum;
	return;
}
void DebugWindow::Impl::update() {
	if (mWrite) {
		if (gDebugFrameNum != UINT_MAX) { // 第一次调用只是刷新
			gDebugOutBuf += "\n";
		}
		HWND hWnd = getWindowHandle();
		RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE | RDW_INTERNALPAINT);
		UpdateWindow(hWnd);
		setWriteFlag(false);
	}
	++gDebugFrameNum;
	if (gDebugFrameNum == UINT_MAX) {
		gDebugFrameNum = 0;
	}
	return;
}
