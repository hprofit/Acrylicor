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

#include "glew.h"
#include "Shader.h"
#include <map>

class ShaderProgram
{
protected:
	GLint m_programID;
	Shader * m_vertexShader;
	Shader * m_fragmentShader;
	std::map<const char *, GLint> m_attributes;
	std::map<const char *, GLint> m_uniforms;

	GLint GetAttributeLocation(const char * attribute);
	GLint GetUniformLocation(const char * uniform);

public:
	ShaderProgram();
	~ShaderProgram();

	GLint GetProgram() const;
	GLint& GetProgramRef();

	void LoadShader(const char * shaderPath, SHADER_TYPE type);

	virtual void AttachShader(Shader& shader);
	void LinkShaders();

	void AddAttribute(const char * name);
	GLint GetAttribute(const char * name);

	void AddUniform(const char * name);
	GLint GetUniform(const char * name);
};

#endif