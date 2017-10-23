/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: RenderManager.h
Purpose: Provides all rendering functionality.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "GameObject.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <map>

// TODO: Don't like
#include "DefaultShaderProgram.h"

class RenderManager
{
private:
	std::map<const char*, ShaderProgram *> m_shaderPrograms;
	ShaderProgram * m_currentProgram;

	RenderManager();
	~RenderManager();
public:
	RenderManager(RenderManager const&) = delete;
	void operator=(RenderManager const&) = delete;

	static RenderManager& GetInstance()
	{
		static RenderManager instance;
		return instance;
	}

	bool Init();
	void FrameStart();
	void RenderGameObject(GameObject& gameObject);
	void RenderGameObject(const Camera& camera, GameObject& gameObject);
	void FrameEnd();

	ShaderProgram * GetShaderProgram(const char * programName);
	ShaderProgram * CreateShaderProgram(const char * programName);
	// TODO: Don't like
	DefaultShaderProgram * CreateDefaultShaderProgram(const char * programName);

	Shader * CreateVertexShader(const char * vertexShaderText);
	Shader * CreateFragmentShader(const char * fragmentShaderText);

	void SelectShaderProgram(const char * programName);
};

#endif