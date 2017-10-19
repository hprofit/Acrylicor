/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShaderProgram.h
Purpose: Houses a Shader Program for that can have individual shaders linked to it
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/16/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include "Shader.h"

class ShaderProgram
{
protected:
	GLint m_programID;
	Shader * m_vertexShader;
	Shader * m_fragmentShader;

public:
	ShaderProgram();
	~ShaderProgram();

	GLint GetProgram() const;
	GLint& GetProgramRef();

	void LoadShader(const char * shaderPath, SHADER_TYPE type);

	virtual void AttachShader(Shader& shader);
	void LinkShaders();

	GLint GetAttributeLocation(const char * attribute);
	GLint GetUniformLocation(const char * uniform);
};

#endif