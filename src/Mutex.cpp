#include "SGK/Threading/Mutex.h"
#include "Mutex.impl.h"

using namespace SGK;

Mutex::Mutex() { mImpl = new Impl(); }
Mutex::~Mutex() {
	delete mImpl;
	mImpl = 0;
}

void Mutex::lock() { mImpl->lock(); return; }
bool Mutex::trylock() { return mImpl->trylock(); }
void Mutex::unlock() { mImpl->unlock(); return; }
