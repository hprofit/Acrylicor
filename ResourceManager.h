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
#include "Mesh.h"

// Data captured by stbi_load
struct STB_Surface {
	unsigned char * data;
	int width;
	int height;
	int channels;
};

class ResourceManager
{
private:
	std::map<const char*, Mesh*> m_meshes;
	std::map<const char*, STB_Surface*> m_textures;

	ResourceManager();
	~ResourceManager();

public:
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;

	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	Mesh * LoadMesh(const char * meshName);
	STB_Surface * LoadTexture(const char * fileName, const char * textureName);
};

#endif