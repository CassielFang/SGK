#include "Shader.impl.h"

#include "SGK/FileGovernor/FileIO.h"
#include "SGK/Math/matrix.h"
#include "glad.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	void Shader::Impl::load() {
		FileIO::instance().load(&mSrc, mShaderName.c_str(), false);
		return;
	}
	void Shader::Impl::compile() {
		GLenum type = 0;
		switch (mType) {
		case ShaderType::Vertex:                type = GL_VERTEX_SHADER;          break;
		case ShaderType::Fragment:              type = GL_FRAGMENT_SHADER;        break;
		case ShaderType::Geometry:              type = GL_GEOMETRY_SHADER;        break;
		case ShaderType::TessellationControl:   type = GL_TESS_CONTROL_SHADER;    break;
		case ShaderType::TessellatioEvaluation: type = GL_TESS_EVALUATION_SHADER; break;
		case ShaderType::Compute:               type = GL_COMPUTE_SHADER;         break;
		}
		mShaderRef = glCreateShader(type);

		const char* src = mSrc->content();
		glShaderSource(mShaderRef, 1, &src, 0);
		glCompileShader(mShaderRef);
		return;
	}
	Shader::Impl::Impl(ShaderType type, const char* name) : mType(type), mShaderName(name), mShaderRef(0), mSrc(nullptr) {
		load();
		compile();
	}
	Shader::Impl::~Impl() {
		glDeleteShader(mShaderRef);
		FileIO::instance().release(&mSrc);
	}
	const char* Shader::Impl::getShaderName() const { return mShaderName.c_str(); }
	unsigned int Shader::Impl::getShaderRef() const { return mShaderRef; }

	Program::Impl::Impl() : mProgramRef(0) { mProgramRef = glCreateProgram(); }
	Program::Impl::~Impl() { glDeleteProgram(mProgramRef); }
	void Program::Impl::link(Shader& shader0) {
		glAttachShader(mProgramRef, shader0.mImpl->getShaderRef());
		glLinkProgram(mProgramRef);
		glDetachShader(mProgramRef, shader0.mImpl->getShaderRef());
		return;
	}
	void Program::Impl::link(Shader& shader0, Shader& shader1) {
		glAttachShader(mProgramRef, shader0.mImpl->getShaderRef());
		glAttachShader(mProgramRef, shader1.mImpl->getShaderRef());
		glLinkProgram(mProgramRef);
		glDetachShader(mProgramRef, shader0.mImpl->getShaderRef());
		glDetachShader(mProgramRef, shader1.mImpl->getShaderRef());
		return;
	}
	void Program::Impl::apply() { glUseProgram(mProgramRef); return; }
	void Program::Impl::setUniform1f(const char* var, float x) {
		unsigned loc = glGetUniformLocation(mProgramRef, var);
		glUniform1f(loc, x);
		return;
	}
	void Program::Impl::setUniformMat4f(const char* var, const Math::mat4& m4) {
		unsigned loc = glGetUniformLocation(mProgramRef, var);
		glUniformMatrix4fv(loc, 1, GL_FALSE, m4.getVal_ptr());
		return;
	}

}

SGK_NAMESPACE_END
