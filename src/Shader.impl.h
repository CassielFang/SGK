#ifndef _SGK_SHADER_IMPL_H_
#define _SGK_SHADER_IMPL_H_

#include "ImplDefinitions.h"
#include "SGK/Graphics/Shader.h"

#include "SGK/FileGovernor/File.h"
#include <string>

SGK_NAMESPACE_BEG

namespace Graphics {

	class Shader::Impl {
	private:
		// 不允许复制或创建空白实例
		Impl();
		Impl(Impl&);
		void operator=(Impl&) {};

		ShaderType mType;
		unsigned mShaderRef;
		std::string mShaderName;
		File* mSrc;

		void load();
		void compile();

	public:
		Impl(ShaderType type, const char* name);
		~Impl();

		const char* getShaderName() const;
		unsigned getShaderRef() const;
	};

	class Program::Impl {
	private:
		// 不允许复制实例
		Impl(Impl&);
		void operator=(Impl&) {};

		unsigned mProgramRef;

	public:
		Impl();
		~Impl();

		void link(Shader& shader0);
		void link(Shader& shader0, Shader& shader1);
		void apply();
		void setUniform1f(const char* var, float x);
		void setUniformMat4f(const char* var, const Math::mat4& m4);
	};

}

SGK_NAMESPACE_END

#endif
