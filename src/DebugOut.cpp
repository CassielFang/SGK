#include "SGK/Base/DebugOut.h"
#include "SGK/Window/WindowCreator.h"
#include "SGK/Window/DebugWindow.h"

#include <sstream>

SGK_NAMESPACE_BEG

_DebugOut DebugOut;
_endl endl;

namespace {
	std::stringstream gSS;
}

void _DebugOut::clear() {
	static DebugWindow dbg = WindowCreator::instance().getDebugWindow();
	dbg.write("", DebugWindow::Mode::Cover);
}

_DebugOut& operator<<(_DebugOut& dout, const char* buf) {
	static DebugWindow dbg = WindowCreator::instance().getDebugWindow();
	dbg.write(buf);
	return dout;
}
_DebugOut& operator<<(_DebugOut& dout, char buf) {
	gSS.str("");
	gSS << buf;
	dout << gSS.str().c_str();
	return dout;
}
_DebugOut& operator<<(_DebugOut& dout, int buf) {
	gSS.str("");
	gSS << buf;
	dout << gSS.str().c_str();
	return dout;
}
_DebugOut& operator<<(_DebugOut& dout, unsigned buf) {
	gSS.str("");
	gSS << buf;
	dout << gSS.str().c_str();
	return dout;
}
_DebugOut& operator<<(_DebugOut& dout, float buf) {
	gSS.str("");
	gSS << buf;
	dout << gSS.str().c_str();
	return dout;
}
_DebugOut& operator<<(_DebugOut& dout, double buf) {
	gSS.str("");
	gSS << buf;
	dout << gSS.str().c_str();
	return dout;
}
_DebugOut& operator<<(_DebugOut& dout, _endl endl) {
	dout << "\n";
	return dout;
}

SGK_NAMESPACE_END
