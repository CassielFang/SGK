#include "SGK/Base/BasicDefinitions.h"
#include "ImplDefinitions.h"

void SGK::_assert(bool exp, const char* filename, int line, const char* message) {
	if (exp == false) {
		throw SGK_impl::Exception_assert(message, filename, line);
	}
	return;
}
