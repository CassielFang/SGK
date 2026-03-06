#include "SGK/Graphics/Core.h"
#include "GraphicsCore.impl.h"

using namespace SGK;

void Graphics::Core::create() { SGK_impl::GraphicsCore_impl::create(); return; }
void Graphics::Core::destroy() { SGK_impl::GraphicsCore_impl::destroy(); return; }
Graphics::Core Graphics::Core::instance() { return Graphics::Core(); }

void Graphics::Core::useVertexBuffer(const VertexBuffer* vertexBuffer) {
	SGK_impl::GraphicsCore_impl::instance()->useVertexBuffer(vertexBuffer);
	return;
}
void Graphics::Core::useIndexBuffer(const IndexBuffer* indexBuffer) {
	SGK_impl::GraphicsCore_impl::instance()->useIndexBuffer(indexBuffer);
	return;
}

void Graphics::Core::draw() { SGK_impl::GraphicsCore_impl::instance()->draw(); return; }
void Graphics::Core::drawInstanced(int count) { SGK_impl::GraphicsCore_impl::instance()->drawInstanced(count); return; }
