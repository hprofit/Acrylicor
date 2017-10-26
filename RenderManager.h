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

#include "AcrylicorTypedefs.h"
#include "GameObject.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include <map>
#include <string>

class RenderManager
{
private:
	std::map<String, ShaderProgram *> m_shaderPrograms;
	ShaderProgram * m_currentProgram;

	RenderManager();
	~RenderManager();

	String LoadTextFile(String fname);
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

	void LoadShaderProgram(String fileName);
	ShaderProgram * GetShaderProgram(String programName);
	ShaderProgram * CreateShaderProgram(String programName);

	Shader * CreateVertexShader(String vertexShaderText);
	Shader * CreateVertexShaderFromFile(String fileName);
	Shader * CreateFragmentShader(String fragmentShaderText);
	Shader * CreateFragmentShaderFromFile(String fileName);

	void SelectShaderProgram(String programName);
};

#endif