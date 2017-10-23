#include "ShaderProgram.h"
#include <iostream>
#include <vector>
#include <string>

ShaderProgram::ShaderProgram() :
	m_vertexShader(NULL),
	m_fragmentShader(NULL)
{
	m_programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if (m_vertexShader) {
		glDetachShader(m_programID, m_vertexShader->GetShaderID());
		delete m_vertexShader;
	}
	if (m_fragmentShader) {
		glDetachShader(m_programID, m_fragmentShader->GetShaderID());
		delete m_fragmentShader;
	}
}

GLint ShaderProgram::GetProgram() const
{
	return m_programID;
}

GLint & ShaderProgram::GetProgramRef()
{
	return m_programID;
}

void ShaderProgram::LoadShader(const char * shaderPath, SHADER_TYPE type)
{
	
}

void ShaderProgram::AttachShader(Shader& shader)
{
	switch (shader.GetShaderType()) {
		case VERTEX_SHADER:
			m_vertexShader = &shader;
			break;
		case FRAGMENT_SHADER:
			m_fragmentShader = &shader;
			break;
	}
	glAttachShader(m_programID, shader.GetShaderID());
}

void ShaderProgram::LinkShaders()
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
}

GLint ShaderProgram::GetAttributeLocation(const char * attribute)
{
	return glGetAttribLocation(m_programID, attribute);
}

GLint ShaderProgram::GetUniformLocation(const char * uniform)
{
	return glGetUniformLocation(m_programID, uniform);
}

void ShaderProgram::AddAttribute(const char * name)
{
	m_attributes[name] = GetAttributeLocation(name);
}

GLint ShaderProgram::GetAttribute(const char * name)
{
	return m_attributes[name];
}

void ShaderProgram::AddUniform(const char * name)
{
	m_uniforms[name] = GetUniformLocation(name);
}

GLint ShaderProgram::GetUniform(const char * name)
{
	return m_uniforms[name];
}
