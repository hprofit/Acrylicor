#include "Shader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Shader::Shader() {}

Shader::Shader(const char * shaderText, SHADER_TYPE type) :
	m_type(type)
{
	GLint result;
	m_shaderID = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	glShaderSource(m_shaderID, 1, &shaderText, 0);
	glCompileShader(m_shaderID);
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		std::cerr << (type == VERTEX_SHADER ? "Vertex" : "Fragment") << " shader failed to compile." << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(m_shaderID, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(m_shaderID);
}

GLuint Shader::GetShaderID() const
{
	return m_shaderID;
}

SHADER_TYPE Shader::GetShaderType() const
{
	return m_type;
}

void Shader::LoadShaderFromFile(const char * shaderFilePath, SHADER_TYPE type)
{
	m_type = type;
	m_shaderID = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	// Read the Shader code from the file
	std::string ShaderCode;
	std::ifstream ShaderStream(shaderFilePath, std::ios::in);
	if (ShaderStream.is_open()) {
		std::string Line = "";
		while (getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}
	else {
		printf("Faild to open %s.\n", shaderFilePath);
		getchar();
		return;
	}

	// Compile Shader
	char const * ShaderSourcePointer = ShaderCode.c_str();
	glShaderSource(m_shaderID, 1, &ShaderSourcePointer, NULL);
	glCompileShader(m_shaderID);

	// Check Shader
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(m_shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}
}


