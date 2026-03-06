#ifndef _SGK_GRAPHICS_INDEXBUFFER_H_
#define _SGK_GRAPHICS_INDEXBUFFER_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	// 顶点缓存
	class IndexBuffer : public NonCopyable {
	public:
		IndexBuffer(int numOfIndices);
		~IndexBuffer();

		// 设置内容
		void setIndices(const unsigned* buf);

		// 获取顶点个数
		int getSize() const;
		// 获取顶点缓存唯一编号
		unsigned getRef() const;

	private:
		int mSize;
		unsigned mIBufferRef;
	};

}

SGK_NAMESPACE_END

#endif
