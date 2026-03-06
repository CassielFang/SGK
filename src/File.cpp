#include "SGK/FileGovernor/File.h"
#include "SGK/Threading/Thread.h"

using namespace SGK;

File::File() : mReady(false), mSize(0), mContent(0) {}
File::~File() {
	while (!isReady()) {
		Thread::sleep(1);
	}
	if (mContent) {
		delete mContent;
		mContent = 0;
	}
}

bool File::isReady() const { return mReady; }
const char* File::content() const {
	strong_assert(mContent);
	return mContent;
}
char File::getByte(int index) const {
	strong_assert(index >= 0 && index < mSize);
	return mContent[index];
}
