#ifndef _SGK_GRAPHICS_VERTEXBUFFER_H_
#define _SGK_GRAPHICS_VERTEXBUFFER_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	// 顶点缓存
	class VertexBuffer : public NonCopyable {
	public:
		VertexBuffer(int numOfVertexes);
		~VertexBuffer();

		// 设置顶点坐标缓存
		void setPositions(const float* positions);
		// 设置纹理坐标缓存
		void setTexCoords(const float* texCoords);
		// 设置法线缓存
		void setNormals(const float* normals);
		// 设置颜色缓存
		void setColors(const float* colors);
		
		// 获取顶点个数
		int getSize() const;
		// 获取顶点缓存唯一编号
		const unsigned* getRef_ptr() const;

	private:
		int mSize;
		// 在glsl中对应的location顺序按照此类中定义的顺序
		unsigned mPBufferRef, mTBufferRef, mNBufferRef, mCBufferRef;
		unsigned mVertexArrayRef;
	};

}

SGK_NAMESPACE_END

#endif
