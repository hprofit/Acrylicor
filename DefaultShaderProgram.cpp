#include "DefaultShaderProgram.h"



DefaultShaderProgram::DefaultShaderProgram()
{
}


DefaultShaderProgram::~DefaultShaderProgram()
{
}

void DefaultShaderProgram::AttachShader(Shader shader)
{
	glAttachShader(m_program, shader);
}

void DefaultShaderProgram::LinkAttributes()
{
	aposition = GetAttributeLocation("position");
	upersp_matrix = GetUniformLocation("persp_matrix");
	uview_matrix = GetUniformLocation("view_matrix");
	umodel_matrix = GetUniformLocation("model_matrix");
	unormal_matrix = GetUniformLocation("normal_matrix");
	ucolor = GetUniformLocation("color");
}
