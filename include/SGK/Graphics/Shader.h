#ifndef _SGK_GRAPHICS_SHADER_h_
#define _SGK_GRAPHICS_SHADER_h_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Math {
	class mat4;
}

namespace Graphics {

	// 着色器，使用OpenGL
	class Shader : public NonCopyable {
	public:
		// 着色器类型
		enum class ShaderType {
			Vertex,
			Fragment,
			Geometry,
			TessellationControl,
			TessellatioEvaluation,
			Compute
		};
		// 需要指定着色器类型和路径
		Shader(ShaderType type, const char* name);
		~Shader();

		friend class Program;
	private:
		class Impl;
		Impl* mImpl;
	};

	// 显卡渲染程序
	class Program : public NonCopyable {
	public:
		Program();
		~Program();

		// 链接着色器
		void link(Shader* shader0);
		// 链接着色器
		void link(Shader* shader0, Shader* shader1);
		// 使用该程序
		void apply();
		// 设置统一变量的值
		void setUniform1f(const char* var, float x);
		// 设置统一变量的值
		void setUniformMat4f(const char* var, const Math::mat4& m4);

	private:
		class Impl;
		Impl* mImpl;
	};

}

SGK_NAMESPACE_END

#endif
