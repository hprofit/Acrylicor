#include "DefaultShaderProgram.h"



DefaultShaderProgram::DefaultShaderProgram() :
	m_linked(false)
{
}


DefaultShaderProgram::~DefaultShaderProgram()
{
}

void DefaultShaderProgram::AttachShader(Shader shader)
{
	glAttachShader(m_programID, shader.GetShaderID());
}

void DefaultShaderProgram::LinkAttributes()
{
	if (!m_linked) {
		aposition = GetAttributeLocation("position");
		anormal = GetAttributeLocation("normal");
		upersp_matrix = GetUniformLocation("persp_matrix");
		uview_matrix = GetUniformLocation("view_matrix");
		umodel_matrix = GetUniformLocation("model_matrix");
		unormal_matrix = GetUniformLocation("normal_matrix");
		ucolor = GetUniformLocation("color");
		m_linked = true;
	}
}
