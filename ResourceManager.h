/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.h
Purpose: Loads Meshes and other commonly used game resources into 
		 memory and manages their instances as well as returns references to them.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <glew.h>
#include <map>
#include <utility>
#include "Mesh.h"
#include "AcrylicorTypedefs.h"
#include "STBSurface.h"

class AcryDebugLine;

class ResourceManager
{
private:
	AcryDebugLine* m_debugLine;
	std::map<String, Mesh*> m_meshes;
	std::map<String, SurfaceTextureBuffer * > m_textures;

	ResourceManager();
	~ResourceManager();

	struct TextureInfo {
		bool hasAlpha;
		float frameWidth, frameHeight;
		int rows, cols;
	};
public:
	ResourceManager(const ResourceManager &) = delete;
	void operator=(const ResourceManager &) = delete;

	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	void CreateDebugLine();
	AcryDebugLine* DebugLine() const { return m_debugLine; }

	Mesh * LoadMesh(String meshName);
	Mesh * GetMesh(String meshName);
	void UnloadMesh(String meshName);

	SurfaceTextureBuffer * LoadTexture(String textureName, String fileName, TextureInfo info);
	SurfaceTextureBuffer * GetTexture(const String textureName);
	void UnloadTexture(String textureName);

	void LoadTexturesFromFile(String fileName);

	void UnloadAll();
};

#endif
