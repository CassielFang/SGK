#ifndef _SGK_GRAPHICS_CORE_IMPL_H_
#define _SGK_GRAPHICS_CORE_IMPL_H_

#include "ImplDefinitions.h"

SGK_NAMESPACE_BEG
namespace Graphics {
	class VertexBuffer;
	class IndexBuffer;
}
SGK_NAMESPACE_END

SGK_IMPL_NAMESPACE_BEG

class GraphicsCore_impl {
private:
	GraphicsCore_impl(GraphicsCore_impl&);
	void operator=(GraphicsCore_impl&) {};

	GraphicsCore_impl();
	~GraphicsCore_impl();
	bool mEnd, mIndexBufferUsed;
	unsigned mVertexArrayRef;
	int mDrawCount;

public:
	static void create();
	static void destroy();
	static GraphicsCore_impl* instance();

	void useVertexBuffer(const SGK::Graphics::VertexBuffer* vertexBuffer);
	void useIndexBuffer(const SGK::Graphics::IndexBuffer* indexBuffer);

	void draw();
	void drawInstanced(int count);
};

SGK_IMPL_NAMESPACE_END

#endif
