#ifndef _SGK_THREAD_IMPL_H_
#define _SGK_THREAD_IMPL_H_

#include "ImplDefinitions.h"
#include "SGK/Threading/Thread.h"
#include "SGK/Threading/Mutex.h"

#include <thread>

SGK_NAMESPACE_BEG

class Thread::Impl {
private:
	std::thread::id mID;
	bool mStart, mFinished;
	std::thread* mThread;
	SGK::Thread* mInst;
	SGK::Mutex mut;
	Impl();

public:
	Impl(SGK::Thread* inst);
	~Impl();

	bool operator==(Impl& t);

	void exe();
	void start();
	void end();
	bool isFinished() const;

	static void sleep(int ms);
};

SGK_NAMESPACE_END

#endif
