#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
	m_program = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
}

GLint ShaderProgram::GetProgram() const
{
	return m_program;
}

GLint & ShaderProgram::GetProgramRef()
{
	return m_program;
}

void ShaderProgram::AttachShader(Shader shader)
{
	glAttachShader(m_program, shader);
}

void ShaderProgram::LinkShaders()
{
	GLint value;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &value);
	if (!value)
		printf("Error linking shaders.\n");
}

GLint ShaderProgram::GetAttributeLocation(const char * attribute)
{
	return glGetAttribLocation(m_program, attribute);
}

GLint ShaderProgram::GetUniformLocation(const char * uniform)
{
	return glGetUniformLocation(m_program, uniform);
}
