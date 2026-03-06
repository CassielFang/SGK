#ifndef _SGK_FILE_H_
#define _SGK_FILE_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

// 文件类，由FileIO全权管理
class File : public NonCopyable{
public:
	// 是否加载完成
	bool isReady() const;
	// 获取文件内容
	const char* content() const;
	// 获取文件指定位置的内容
	char getByte(int index) const;

	friend class Loader;
private:
	File();
	~File();

	bool mReady;
	int mSize;
	char* mContent;
};

SGK_NAMESPACE_END

#endif
