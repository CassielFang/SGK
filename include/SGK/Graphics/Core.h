#ifndef _SGK_GRAPHICS_CORE_H_
#define _SGK_GRAPHICS_CORE_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	class VertexBuffer;
	class IndexBuffer;

	// Graphics模块的核心，负责整体图形绘制流程
	class Core {
	public:
		static void create();
		static void destroy();
		// 获取单例类实例
		static Core instance();

		// 使用指定顶点缓存
		void useVertexBuffer(const VertexBuffer* vertexBuffer);
		// 使用指定索引缓存
		void useIndexBuffer(const IndexBuffer* indexBuffer);

		// 执行绘制
		void draw();
		// 执行绘制，可选副本数量，但要另外编写相应的shader
		void drawInstanced(int count);
	};

}

SGK_NAMESPACE_END

#endif
