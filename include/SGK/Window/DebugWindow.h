#ifndef _SGK_DEBUGWINDOW_H_
#define _SGK_DEBUGWINDOW_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 调试信息输出窗口，DebugOut定向于此
class DebugWindow : public Permitted {
public:
	DebugWindow(SGKcharter* charter);
	~DebugWindow();

	// 写入模式
	enum class Mode {
		Cover,
		Add,
		Return
	};
	// 直接写入内容
	void write(const char* buf, Mode mode = Mode::Add);

	class Impl;
private:
	Impl* mImpl;
	SGKcharter* mCharter;
};

SGK_NAMESPACE_END

#endif
