#include "Thread.impl.h"
#include "SGK/Threading/Mutex.h"

using namespace SGK;

Thread::Impl::Impl(SGK::Thread* inst) : mID(), mStart(false), mFinished(false), mThread(0), mInst(inst) { }
Thread::Impl::Impl::~Impl() {
	strong_assert(mFinished);
	mThread->join();
	delete mThread;
	mThread = 0;
}

bool Thread::Impl::operator==(Impl& t) {
	strong_assert(mStart);
	return (this->mID == t.mID);
}

void Thread::Impl::exe() {
	mut.lock();
	mID = std::this_thread::get_id();
	mut.unlock();
	mInst->execute();
	end();
	return;
}
void Thread::Impl::start() {
	mut.lock();
	mStart = true;
	mThread = new std::thread(&Impl::exe, this);
	mut.unlock();
	return;
}
void Thread::Impl::end() {
	mut.lock();
	mFinished = true;
	mut.unlock();
	return;
}
bool Thread::Impl::isFinished() const { return mFinished; }

void Thread::Impl::sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	return;
}
