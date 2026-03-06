#include "SGK/FileGovernor/FileIO.h"
#include "FileIO.impl.h"

using namespace SGK;

void FileIO::create() { SGK_impl::FileIO_impl::create(); return; }
void FileIO::destroy() { SGK_impl::FileIO_impl::destroy(); return; }
FileIO FileIO::instance() { return FileIO(); }

void FileIO::load(File** file, const char* path, bool threading) { SGK_impl::FileIO_impl::instance()->load(file, path, threading); return; }
void FileIO::release(File** file) { SGK_impl::FileIO_impl::instance()->release(file); return; }

void FileIO::update() { SGK_impl::FileIO_impl::instance()->update(); return; }
