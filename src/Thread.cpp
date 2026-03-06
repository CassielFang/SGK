#include "SGK/Threading/Thread.h"
#include "Thread.impl.h"

using namespace SGK;

Thread::Thread() {
	mImpl = new Impl(this);
}
Thread::~Thread() {
	strong_assert(mImpl->isFinished());
	delete mImpl;
	mImpl = 0;
}

void Thread::start() { mImpl->start(); return; }
void Thread::wait() {
	while (!isFinished()) {
		sleep(1);
	}
	return;
}
bool Thread::isFinished() const { return mImpl->isFinished(); }
void Thread::sleep(int ms) { Impl::sleep(ms); return; }
