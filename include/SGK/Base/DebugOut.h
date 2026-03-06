#ifndef _SGK_DEBUGOUT_H_
#define _SGK_DEBUGOUT_H_

#include "BasicDefinitions.h"

SGK_NAMESPACE_BEG

class _endl { }; // 换行

// 用于实现cout的基本功能，但请尽量减少单帧内输出的字符量，避免占用过多性能导致帧率下降
class _DebugOut {
public:
	void clear();

	friend _DebugOut& operator<<(_DebugOut& dout, const char* buf);
	friend _DebugOut& operator<<(_DebugOut& dout, char        buf);
	friend _DebugOut& operator<<(_DebugOut& dout, int         buf);
	friend _DebugOut& operator<<(_DebugOut& dout, unsigned    buf);
	friend _DebugOut& operator<<(_DebugOut& dout, float       buf);
	friend _DebugOut& operator<<(_DebugOut& dout, double      buf);
	friend _DebugOut& operator<<(_DebugOut& dout, _endl endl);
};

_DebugOut& operator<<(_DebugOut& dout, const char* buf);
_DebugOut& operator<<(_DebugOut& dout, char        buf);
_DebugOut& operator<<(_DebugOut& dout, int         buf);
_DebugOut& operator<<(_DebugOut& dout, unsigned    buf);
_DebugOut& operator<<(_DebugOut& dout, float       buf);
_DebugOut& operator<<(_DebugOut& dout, double      buf);
_DebugOut& operator<<(_DebugOut& dout, _endl endl);

extern _DebugOut DebugOut;
extern _endl endl;

SGK_NAMESPACE_END

#endif
