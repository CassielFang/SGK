#include "ImplDefinitions.h"

#include <Windows.h>

SGK_NAMESPACE_BEG

SGKcharter::SGKcharter() : mRelease(false), mLock(false) { }
SGKcharter::~SGKcharter() { assertEx(mRelease, "You break into SGK's secret chamber! It's not allowed!"); }

void SGKcharter::lock() { mLock = true; return; }
void SGKcharter::release() { mRelease = true; return; }
bool SGKcharter::isLocked() const { return mLock; }

SGK_NAMESPACE_END

using namespace SGK_impl;

Exception_assert::Exception_assert(const char* msg, const char* file, int line) :
	mMessage(msg), mFile(file), mLine(line) { }
const char* Exception_assert::getMessage() const { return mMessage; }
const char* Exception_assert::getInfo_file() const { return mFile; }
const int Exception_assert::getInfo_line() const { return mLine; }

SGKClock* gClock;
SGKClock::SGKClock() {
	LARGE_INTEGER clkfreq, starttm;
	assertEx(!gClock, "Only allowed to generate one global clock!");
	assertEx(QueryPerformanceFrequency(&clkfreq), "Failed to get query performance frequency!");
	QueryPerformanceCounter(&starttm);
	mClockFrequency = static_cast<double>(clkfreq.QuadPart);
	mStartTime = static_cast<long long>(starttm.QuadPart);
	mTimeNow = mStartTime;
}
SGKClock::~SGKClock() { assertEx(mStartTime < 0, "The global clock is not allowed to be destroyed actively!"); }
void SGKClock::create() {
	gClock = new SGKClock();
	return;
}
void SGKClock::destroy() {
	gClock->mStartTime = -1;
	delete gClock;
	gClock = 0;
	return;
}
SGKClock* SGKClock::instance() {
	return gClock;
}
unsigned SGKClock::getGlobalTime() {
	LARGE_INTEGER tmnow;
	QueryPerformanceCounter(&tmnow);
	mTimeNow = static_cast<long long>(tmnow.QuadPart);
	return static_cast<unsigned>((mTimeNow - mStartTime) / mClockFrequency * 1000);
}
