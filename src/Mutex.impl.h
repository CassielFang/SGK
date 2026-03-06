#ifndef _SGK_MUTEX_IMPL_H_
#define _SGK_MUTEX_IMPL_H_

#include "ImplDefinitions.h"
#include "SGK/Threading/Mutex.h"

#include <mutex>

SGK_NAMESPACE_BEG

class Mutex::Impl {
private:
	std::mutex mMut;

public:
	void lock();
	bool trylock();
	void unlock();
};

SGK_NAMESPACE_END

#endif
