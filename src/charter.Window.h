#ifndef _SGK_CHARTER_WINDOW_H_
#define _SGK_CHARTER_WINDOW_H_

#include "ImplDefinitions.h"
#include "SGKWindow.impl.h"

SGK_IMPL_NAMESPACE_BEG

class Windowcharter : public SGK::SGKcharter {
private:
	Windowcharter();

public:
	Windowcharter(SGKWindow_impl* SGKwindow) : mSGKWindow(SGKwindow) { }
	SGKWindow_impl* mSGKWindow;
};

SGK_IMPL_NAMESPACE_END

#endif
