#ifndef _SGK_IMPLDEFINITION_H_
#define _SGK_IMPLDEFINITION_H_

#include "SGK/Base/BasicDefinitions.h"

#define SGK_IMPL_NAMESPACE_BEG namespace SGK_impl {
#define SGK_IMPL_NAMESPACE_END }

#define assertEx(expression, message) SGK::_assert(expression, "SGK Core", 0, message)
#define invalid_array_index() SGK::_assert(false, "SGK Core", 0, "Array index out of bound!")
#define invalid_operation(expression) SGK::_assert(expression, "SGK Core", 0, "Don't attempt to break into SGK's secret chamber!")

SGK_NAMESPACE_BEG

class SGKcharter {
private:
	SGKcharter(SGKcharter&);
	void operator=(SGKcharter&) {};

	bool mLock, mRelease;

public:
	SGKcharter();
	virtual ~SGKcharter();

	void lock();
	void release();

	bool isLocked() const;
};

SGK_NAMESPACE_END

SGK_IMPL_NAMESPACE_BEG

class Exception_assert {
private:
	Exception_assert();
	const char* mMessage;
	const char* mFile;
	const int mLine;

public:
	Exception_assert(const char* msg, const char* file, int line);
	const char* getMessage() const;
	const char* getInfo_file() const;
	const int getInfo_line() const;
};

class SGKClock {
private:
	// 不允许复制实例
	SGKClock(SGKClock&);
	void operator=(SGKClock&) {};
	
	SGKClock();
	~SGKClock();
	double mClockFrequency;
	long long mStartTime, mTimeNow;

public:
	static void create();
	static void destroy();
	static SGKClock* instance();

	unsigned getGlobalTime();
};

SGK_IMPL_NAMESPACE_END

#endif
