#include "Mutex.impl.h"

using namespace SGK;

void Mutex::Impl::lock() { mMut.lock(); return; }
bool Mutex::Impl::trylock() { return mMut.try_lock(); }
void Mutex::Impl::unlock() { mMut.unlock(); return; }
