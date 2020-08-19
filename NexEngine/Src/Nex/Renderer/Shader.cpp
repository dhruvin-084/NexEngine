#include"nexpch.h"

#include<glad/glad.h>
#include"Nex/log.h"
#include"Shader.h"

namespace Nex {
	Shader::Shader(std::string& vertexSrc, std::string& fragmentSrc) {
		const char* vShaderCode = vertexSrc.c_str();
		const char* fShaderCode = fragmentSrc.c_str();

		unsigned int fragment, vertex;
		int success;
		char infolog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infolog);
			NEX_CORE_ERROR("VERTEX SHADER COMPILE FAILED::");
			NEX_CORE_ERROR("{0}", infolog);
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infolog);
			NEX_CORE_ERROR("FRAGMENT SHADER COMPILE FAILED::");
			NEX_CORE_ERROR("{0}", infolog);
		}

		m_RenderID = glCreateProgram();
		glAttachShader(m_RenderID, vertex);
		glAttachShader(m_RenderID, fragment);
		glLinkProgram(m_RenderID);

		glGetProgramiv(m_RenderID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_RenderID, 512, NULL, infolog);
			NEX_CORE_ERROR("SHADER PROGRAM LINKING FAILED::");
			NEX_CORE_ERROR("{0}", infolog);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	Shader::~Shader()
	{
		glDeleteProgram(m_RenderID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RenderID);
	}
	void Shader::Unbind()
	{
		glUseProgram(0);
	}
}