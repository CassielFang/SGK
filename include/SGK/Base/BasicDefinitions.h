#ifndef _SGK_BASICDEFINITIONS_H_
#define _SGK_BASICDEFINITIONS_H_

constexpr int SGK_VISION_MAJOR = 1;
constexpr int SGK_VISION_MINOR = 0;

#define SGK_NAMESPACE_BEG namespace SGK {
#define SGK_NAMESPACE_END }

SGK_NAMESPACE_BEG

// 用于单例类的配套工具类，意为许可证
class SGKcharter;

// 如果exp为false(0)，则终止运行
void _assert(bool exp, const char* filename, int line, const char* message);

// 如果exp为false(0)，则终止运行
#define strong_assert(expression) SGK::_assert(expression, __FILE__, __LINE__, #expression)
#ifdef _DEBUG
// 如果exp为false(0)，则终止运行
#define assert(expression) SGK::_assert(expression, __FILE__, __LINE__, #expression)
#else
#define assert(expression) (expression)
#endif

// 继承自此基类的派生类不可复制
class NonCopyable {
public:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

// 继承自此基类的派生类必须接受SGKcharter的指针，不允许复制或创建空类
class Permitted {
public:
	Permitted(SGKcharter*) {};
	virtual ~Permitted() = default;

	Permitted() = delete;
	Permitted(const Permitted&) = delete;
	Permitted& operator=(const Permitted&) = delete;
};

SGK_NAMESPACE_END

#endif
