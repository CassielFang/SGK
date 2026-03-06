#include "SGK/Graphics/IndexBuffer.h"

#include "glad.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	IndexBuffer::IndexBuffer(int numOfIndices) : mSize(numOfIndices), mIBufferRef(0) {
		glGenBuffers(1, &mIBufferRef);
	}
	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &mIBufferRef);
	}

	void IndexBuffer::setIndices(const unsigned* buf) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBufferRef);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(mSize) * 4, buf, GL_STATIC_DRAW);
	}

	int IndexBuffer::getSize() const { return mSize; }
	unsigned IndexBuffer::getRef() const { return mIBufferRef; }

}

SGK_NAMESPACE_END
