#ifndef _SGK_MUTEX_H_
#define _SGK_MUTEX_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 互斥锁对象，用于基本的线程安全
class Mutex : NonCopyable {
public:
	Mutex();
	~Mutex();

	// 加锁，若已经加锁则休眠
	void lock();
	// 尝试加锁，不会休眠
	bool trylock();
	// 解锁
	void unlock();

private:
	class Impl;
	Impl* mImpl;
};

SGK_NAMESPACE_END

#endif
