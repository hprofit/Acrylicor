#include "Shader.h"
#include <iostream>

Shader::Shader(const char * shaderText, SHADER_TYPE type)
{
	GLint value;
	m_shader = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	glShaderSource(m_shader, 1, &shaderText, 0);
	glCompileShader(m_shader);
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &value);
	if (!value) {
		std::cerr << (type == VERTEX_SHADER ? "Vertex" : "Fragment") << " shader failed to compile." << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(m_shader, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
}

Shader::~Shader()
{
}

Shader::operator GLuint() const
{
	return m_shader;
}


