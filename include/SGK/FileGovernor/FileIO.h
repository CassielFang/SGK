#ifndef _SGK_FILEIO_H_
#define _SGK_FILEIO_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

class File;

// 文件管理类，负责文件读写，可选是否使用多线程
class FileIO {
public:
	static void create();
	static void destroy();
	// 获取单例类的实例
	static FileIO instance();

	// 载入文件，默认多线程加载
	void load(File** file, const char* path, bool threading = true);
	// void write(File** file, const char* path, const char* content);
	// 释放文件，会将文件内容清空
	void release(File** file);

	void update();
};

SGK_NAMESPACE_END

#endif
