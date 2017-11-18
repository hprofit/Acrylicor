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

void ShaderProgram::LoadShader(String shaderPath, SHADER_TYPE type)
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

GLint ShaderProgram::_GetAttributeLocation(String attribute)
{
	return glGetAttribLocation(m_programID, attribute.c_str());
}

GLint ShaderProgram::_GetUniformLocation(String uniform)
{
	return glGetUniformLocation(m_programID, uniform.c_str());
}

void ShaderProgram::AddAttribute(String name)
{
	m_attributes[name] = _GetAttributeLocation(name);
}

GLint ShaderProgram::GetAttribute(String name)
{
	return m_attributes[name];
}

void ShaderProgram::AddUniform(String name)
{
	m_uniforms[name] = _GetUniformLocation(name);
}

GLint ShaderProgram::GetUniform(String name)
{
	return m_uniforms[name];
}
