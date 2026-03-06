#ifndef _SGK_FILEIO_IMPL_H_
#define _SGK_FILEIO_IMPL_H_

#include "ImplDefinitions.h"
#include "SGK/FileGovernor/File.h"

#include "SGK/Threading/Thread.h"
#include <string>
#include <queue>

SGK_NAMESPACE_BEG

class Loader : public Thread {
public:
	Loader(File** file, const char* path);
	~Loader();

	void execute();
	static void instant(File** file, const char* path);
	static void release(File** file);

private:
	// 不允许复制或创建空白实例
	Loader();
	void operator=(Loader&) {};

	std::string mPath;
	File** mFile;
};

SGK_NAMESPACE_END

SGK_IMPL_NAMESPACE_BEG

// FileIO的代理类
class FileIO_impl {
private:
	// 不允许复制或创建空白实例
	FileIO_impl();
	~FileIO_impl();
	FileIO_impl(FileIO_impl&);
	void operator=(FileIO_impl&) {};

	struct Request {
		std::string path;
		SGK::File** file;
	};
	std::queue<SGK::Loader*> mLoadingList;
	std::queue<Request> mRequestList;

public:
	static void create();
	static void destroy();
	static FileIO_impl* instance();

	void load(SGK::File** file, const char* path, bool threading = true);
	void release(SGK::File** file);
	void update();
};

SGK_IMPL_NAMESPACE_END

#endif
