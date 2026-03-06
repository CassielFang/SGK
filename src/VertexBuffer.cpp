#include "SGK/Graphics/VertexBuffer.h"

#include "glad.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	VertexBuffer::VertexBuffer(int numOfVertexes) : mSize(numOfVertexes), mPBufferRef(0), mTBufferRef(0), mNBufferRef(0), mCBufferRef(0), mVertexArrayRef(0) {
		glGenVertexArrays(1, &mVertexArrayRef);
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(4, &mPBufferRef);
	}

	void VertexBuffer::setPositions(const float* positions) {
		glBindVertexArray(mVertexArrayRef);
		if (!mPBufferRef) {
			glGenBuffers(1, &mPBufferRef);
		}
		glBindBuffer(GL_ARRAY_BUFFER, mPBufferRef);
		glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(mSize) * 12, reinterpret_cast<const void*>(positions), GL_STATIC_DRAW);
		return;
	}
	void VertexBuffer::setTexCoords(const float* texCoords) {
		glBindVertexArray(mVertexArrayRef);
		if (!mTBufferRef) {
			glGenBuffers(1, &mTBufferRef);
		}
		glBindBuffer(GL_ARRAY_BUFFER, mTBufferRef);
		glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(mSize) * 8, reinterpret_cast<const void*>(texCoords), GL_STATIC_DRAW);
		return;
	}
	void VertexBuffer::setNormals(const float* normals) {
		glBindVertexArray(mVertexArrayRef);
		if (!mNBufferRef) {
			glGenBuffers(1, &mNBufferRef);
		}
		glBindBuffer(GL_ARRAY_BUFFER, mNBufferRef);
		glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(mSize) * 12, reinterpret_cast<const void*>(normals), GL_STATIC_DRAW);
		return;
	}
	void VertexBuffer::setColors(const float* colors) {
		glBindVertexArray(mVertexArrayRef);
		if (!mCBufferRef) {
			glGenBuffers(1, &mCBufferRef);
		}
		glBindBuffer(GL_ARRAY_BUFFER, mCBufferRef);
		glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(mSize) * 16, reinterpret_cast<const void*>(colors), GL_STATIC_DRAW);
		return;
	}

	int VertexBuffer::getSize() const { return mSize; }
	const unsigned* VertexBuffer::getRef_ptr() const { return &mPBufferRef; }

}

SGK_NAMESPACE_END
