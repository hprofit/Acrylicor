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
#include "ShaderProgram.h"
#include "Shader.h"
#include "STBSurface.h"
#include <map>
#include <string>
#include "Matrix4x4.h"

class ResourceManager;
class SpriteComponent;
class ScrollingSpriteComponent;
class PhysicsComponent;

class RenderManager
{
private:
	ResourceManager& resourceMngr;
	std::map<String, ShaderProgram *> m_shaderPrograms;
	ShaderProgram * m_currentProgram;
	String m_debugShaderName;
	bool m_debugMode;

	RenderManager();
	~RenderManager();

	String _LoadTextFile(String fname);
	void _RenderPhysicsBody(GameObject & camera, GameObject & gameObject);
	void _RenderSprite(SpriteComponent* sComp);
	void _RenderScrollingSprite(ScrollingSpriteComponent* sComp);
	void _RenderGameObject(GameObject& gameObject);
	void _SelectShaderProgram(GameObject& gameObject);
public:
	RenderManager(const RenderManager &) = delete;
	void operator=(const RenderManager &) = delete;

	static RenderManager& GetInstance()
	{
		static RenderManager instance;
		return instance;
	}

	bool Init();
	void FrameStart();
	void RenderGameObject(GameObject& gameObject);
	void RenderGameObject(GameObject& camera, GameObject& gameObject);

	void RenderSquare(GameObject & camera, float width, float height, float rotate, float x, float y);
	void RenderCircle(GameObject & camera, float radius, float x, float y);

	void FrameEnd();

	void SetDebugShaderName(String shaderName) { m_debugShaderName = shaderName; }
	void SetDebugMode(bool debugMode) { m_debugMode = debugMode; }
	void LoadShaderProgram(String fileName);
	ShaderProgram * GetShaderProgram(String programName);
	ShaderProgram * CreateShaderProgram(String programName);

	Shader * CreateVertexShader(String vertexShaderText);
	Shader * CreateVertexShaderFromFile(String fileName);
	Shader * CreateFragmentShader(String fragmentShaderText);
	Shader * CreateFragmentShaderFromFile(String fileName);

	void SelectShaderProgram(String programName);

	GLuint CreateTextureBuffer(const STB_Surface * const stbSurface);
};

#endif