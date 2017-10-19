/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DefaultShaderProgram.h
Purpose: Default Shader program with ties to default shaders. This is for testing.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/16/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef DEFAULT_SHADER_PROGRAM_H
#define DEFAULT_SHADER_PROGRAM_H

#include "ShaderProgram.h"

class DefaultShaderProgram : 
	public ShaderProgram
{
public:
	GLint aposition,
		upersp_matrix,
		uview_matrix,
		umodel_matrix,
		unormal_matrix,
		ucolor;

	DefaultShaderProgram();
	~DefaultShaderProgram();

	virtual void AttachShader(Shader shader);

	virtual void LinkAttributes();
};

#endif