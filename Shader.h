/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.h
Purpose: An invidual vertex or fragment/pixel shader. Can be linked to a ShaderProgram
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/16/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

const enum SHADER_TYPE {
	VERTEX_SHADER = 0,
	FRAGMENT_SHADER = 1
};

class Shader
{
private:
	GLuint m_shaderID;
	SHADER_TYPE m_type;

public:
	Shader();
	Shader(const char * shaderText, SHADER_TYPE type);
	~Shader();

	GLuint GetShaderID() const;
	SHADER_TYPE GetShaderType() const;

	void LoadShaderFromFile(const char * shaderFilePath, SHADER_TYPE type);
};

#endif