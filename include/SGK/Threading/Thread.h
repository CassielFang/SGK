#ifndef _SGK_THREAD_H_
#define _SGK_THREAD_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 自定义线程的基类
class Thread : public NonCopyable {
public:
	Thread();
	virtual ~Thread();

	// 调用时创建一个新新线程执行execute()
	void start();
	// 调用时一直等待直到execute()执行结束
	void wait();
	// 判断execute()是否执行结束
	bool isFinished() const;
	// 全局函数，调用的线程休眠指定时长（毫秒）
	static void sleep(int ms);

	// 该函数需要派生类实现
	virtual void execute() = 0;

private:
	class Impl;
	Impl* mImpl;
};

SGK_NAMESPACE_END

#endif
