#include "GraphicsCore.impl.h"
#include "SGK/Graphics/VertexBuffer.h"
#include "SGK/Graphics/IndexBuffer.h"

#include "glad.h"

using namespace SGK_impl;

static GraphicsCore_impl* gGraphicsCore = nullptr;

GraphicsCore_impl::GraphicsCore_impl() : mEnd(false), mIndexBufferUsed(false), mVertexArrayRef(0), mDrawCount(0) {
	invalid_operation(!gGraphicsCore);
}
GraphicsCore_impl::~GraphicsCore_impl() {
	invalid_operation(gGraphicsCore);
}

void GraphicsCore_impl::create() {
	gGraphicsCore = new GraphicsCore_impl();
	return;
}
void GraphicsCore_impl::destroy() {
	gGraphicsCore->mEnd = true;
	delete gGraphicsCore;
	gGraphicsCore = nullptr;
	return;
}
GraphicsCore_impl* GraphicsCore_impl::instance() { return gGraphicsCore; }

void GraphicsCore_impl::useVertexBuffer(const SGK::Graphics::VertexBuffer* vertexBuffer) {
	mVertexArrayRef = vertexBuffer->getRef_ptr()[4];
	mDrawCount = vertexBuffer->getSize();
	glBindVertexArray(mVertexArrayRef);
	int i = 0;
	if (vertexBuffer->getRef_ptr()[0]) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRef_ptr()[0]);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i);
		++i;
	}
	if (vertexBuffer->getRef_ptr()[1]) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRef_ptr()[1]);
		glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i);
		++i;
	}
	if (vertexBuffer->getRef_ptr()[2]) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRef_ptr()[2]);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i);
		++i;
	}
	if (vertexBuffer->getRef_ptr()[3]) {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRef_ptr()[3]);
		glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i);
		++i;
	}
	return;
}
void GraphicsCore_impl::useIndexBuffer(const SGK::Graphics::IndexBuffer* indexBuffer) {
	if (mVertexArrayRef) {
		mIndexBufferUsed = true;
		mDrawCount = indexBuffer->getSize();
		glBindVertexArray(mVertexArrayRef);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getRef());
	}
	return;
}

void GraphicsCore_impl::draw() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(mVertexArrayRef);
	if (mIndexBufferUsed) {
		glDrawElements(GL_TRIANGLES, mDrawCount, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, mDrawCount);
	}
	mIndexBufferUsed = false;
	mVertexArrayRef = 0;
	mDrawCount = 0;
	return;
}
void GraphicsCore_impl::drawInstanced(int count) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArraysInstanced(GL_TRIANGLES, 0, mDrawCount, count);
	return;
}


