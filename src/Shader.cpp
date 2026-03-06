#include "SGK/Graphics/Shader.h"
#include "Shader.impl.h"

using namespace SGK;
using namespace Graphics;

Shader::Shader(ShaderType type, const char* name) { mImpl = new Impl(type, name); }
Shader::~Shader() { delete mImpl; }

Program::Program() { mImpl = new Impl; }
Program::~Program() { delete mImpl; }
void Program::link(Shader* shader0) { mImpl->link(*shader0); return; }
void Program::link(Shader* shader0, Shader* shader1) { mImpl->link(*shader0, *shader1); return; }
void Program::apply() { mImpl->apply(); return; }
void Program::setUniform1f(const char* var, float x) { mImpl->setUniform1f(var, x); return; }
void Program::setUniformMat4f(const char* var, const Math::mat4& m4) { mImpl->setUniformMat4f(var, m4); return; }

/*string readShaderFile(const char* filePath)
	{
		string content;
		ifstream fileStream(filePath, ios::in);
		if (!fileStream.is_open())
		{
			throw "Unable to open file.";
		}
		string line = "";
		while (!fileStream.eof())
		{
			getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
		return content;
	}
	bool checkOpenGLError()
	{
		bool foundError = false;
		int glErr = glGetError();
		while (glErr != GL_NO_ERROR)
		{
			DebugOut << "glError: " << glErr << endl;
			foundError = true;
			glErr = glGetError();
		}
		return foundError;
	}
	void printShaderLog(GLuint shader)
	{
		int len = 0;
		int chWrittn = 0;
		char* log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			log = (char*)malloc(len);
			glGetShaderInfoLog(shader, len, &chWrittn, log);
			DebugOut << "Shader Info Log: " << log << endl;
			free(log);
		}
	}
	void printProgramLog(int prog)
	{
		int len = 0;
		int chWrittn = 0;
		char* log;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
		if (len > 0) {
			log = (char*)malloc(len);
			glGetProgramInfoLog(prog, len, &chWrittn, log);
			DebugOut << "Program Info Log: " << log << endl;
			free(log);
		}
	}
	GLuint prepareShader(int shaderTYPE, const char* shaderPath)
	{
		GLint shaderCompiled;
		string shaderStr = readShaderFile(shaderPath);
		const char* shaderSrc = shaderStr.c_str();
		GLuint shaderRef = glCreateShader(shaderTYPE);

		if (shaderRef == 0 || shaderRef == GL_INVALID_ENUM)
		{
			printf("Error: Could not create shader \"%s\" of type:%d\n", shaderPath, shaderTYPE);
			return 0;
		}

		glShaderSource(shaderRef, 1, &shaderSrc, NULL);
		glCompileShader(shaderRef);
		checkOpenGLError();

		glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			if (shaderTYPE == GL_VERTEX_SHADER) DebugOut << "Vertex ";
			if (shaderTYPE == GL_TESS_CONTROL_SHADER) DebugOut << "Tess Control ";
			if (shaderTYPE == GL_TESS_EVALUATION_SHADER) DebugOut << "Tess Eval ";
			if (shaderTYPE == GL_GEOMETRY_SHADER) DebugOut << "Geometry ";
			if (shaderTYPE == GL_FRAGMENT_SHADER) DebugOut << "Fragment ";
			if (shaderTYPE == GL_COMPUTE_SHADER) DebugOut << "Compute ";
			DebugOut << "shader compilation error for shader: '" << shaderPath << "'." << endl;
			printShaderLog(shaderRef);
		}
		return shaderRef;
	}
	int finalizeShaderProgram(GLuint sprogram)
	{
		GLint linked;
		glLinkProgram(sprogram);
		checkOpenGLError();
		glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
		if (linked != 1)
		{
			DebugOut << "linking failed" << endl;
			printProgramLog(sprogram);
		}
		return sprogram;
	}
	GLuint createShaderProgram(const char* vp, const char* fp)
	{
		GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
		GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
		GLuint vfprogram = glCreateProgram();
		glAttachShader(vfprogram, vShader);
		glAttachShader(vfprogram, fShader);
		finalizeShaderProgram(vfprogram);
		glDetachShader(vfprogram, vShader);
		glDetachShader(vfprogram, fShader);
		glDeleteShader(vShader);
		glDeleteShader(fShader);
		return vfprogram;
	}*/
