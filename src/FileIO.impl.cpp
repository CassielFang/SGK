#include "FileIO.impl.h"
#include <fstream>

namespace SGK {

	Loader::Loader(File** file, const char* path) : mPath(path), mFile(file) {
		start();
	}
	Loader::~Loader() { wait(); }

	void Loader::execute() {
		instant(mFile, mPath.c_str());
		return;
	}
	void Loader::instant(File** file, const char* path) {
		(*file) = new File;
		std::ifstream in(path, std::ifstream::binary);
		in.seekg(0, std::ifstream::end);
		int size = static_cast<int>(in.tellg());
		(*file)->mSize = size + 1;
		in.seekg(0, std::ifstream::beg);
		(*file)->mContent = new char[size + 1];
		in.read((*file)->mContent, size);
		(*file)->mContent[size] = '\0';
		(*file)->mReady = true;
		in.close();
		return;
	}
	void Loader::release(File** file) {
		delete (*file);
		return;
	}

}

using namespace SGK_impl;

FileIO_impl* gFileIO;
FileIO_impl::FileIO_impl() { invalid_operation(!gFileIO); }
FileIO_impl::~FileIO_impl() { invalid_operation(mLoadingList.size() == 0); }

void FileIO_impl::create() {
	gFileIO = new FileIO_impl;
	return;
}
void FileIO_impl::destroy() {
	invalid_operation(gFileIO);
	delete gFileIO;
	gFileIO = 0;
	return;
}
FileIO_impl* FileIO_impl::instance() { return gFileIO; }

void FileIO_impl::load(SGK::File** file, const char* path, bool threading) {
	if (*file) {
		if ((*file)->isReady()) {
			return;
		}
		else {
			strong_assert("Unprepared file!");
		}
	}
	if (threading) {
		mRequestList.push(Request{ path, file });
		update();
	}
	else {
		SGK::Loader::instant(file, path);
	}
	return;
}
void FileIO_impl::release(SGK::File** file) {
	if ((*file) && (*file)->isReady()) {
		SGK::Loader::release(file);
		(*file) = 0;
	}
	return;
}
void FileIO_impl::update() {
	while (mLoadingList.size() > 0 && mLoadingList.front()->isFinished()) {
		SGK::Loader* l = mLoadingList.front();
		mLoadingList.pop();
		delete l;
		l = 0;
	}
	while (mRequestList.size() > 0 && mLoadingList.size() < 3) {
		Request& r = mRequestList.front();
		SGK::Loader* l = new SGK::Loader(r.file, r.path.c_str());
		mLoadingList.push(l);
		mRequestList.pop();
	}
	return;
}
