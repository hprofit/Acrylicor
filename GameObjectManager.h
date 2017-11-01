/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.h
Purpose: Object pool manager - stores a pool of GameObject instances, handles creating instances and destroying them.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include "Camera.h"
#include "AcrylicorTypedefs.h"
#include <vector>
#include "json.hpp"

class GameObjectManager
{
private:
	int m_maxObjects;
	std::vector<GameObject * > m_gameObjects;

	GameObjectManager() = delete;
	GameObjectManager(int maxObjects);
	~GameObjectManager();
public:
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;

	static GameObjectManager& GetInstance(int maxObjects = 1024)
	{
		static GameObjectManager instance(maxObjects);
		return instance;
	}

	void SpawnGameObject(String objectType);
	void SpawnGameObjectFromFile( nlohmann::json j);
	void DestroyGameObject(GameObject * gObject);

	void UpdateGameObjects(double deltaTime);
	void RenderGameObjects(Camera & camera);
};

#endif