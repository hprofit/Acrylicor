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
#include "Component.h"
#include "AcrylicorTypedefs.h"
#include <vector>
#include "json.hpp"

class EventManager;
class GameObjectManager
{
private:
	unsigned int m_maxObjects;
	std::vector<GameObject * > m_gameObjects;
	std::vector<Component * > m_cameras;
	GameObject * m_activeCamera;

	friend EventManager;

	GameObjectManager() = delete;
	GameObjectManager(unsigned int maxObjects);
	~GameObjectManager();

	void _SetActiveCamera(GameObject* gObject);
	GameObject * _SpawnObject(GameObject* gameObject);
public:
	GameObjectManager(const GameObjectManager &) = delete;
	void operator=(const GameObjectManager &) = delete;

	static GameObjectManager& GetInstance(unsigned int maxObjects = 2048)
	{
		static GameObjectManager instance(maxObjects);
		return instance;
	}

	GameObject * SpawnGameObject(String objectType);
	GameObject * SpawnGameObject(String objectType, GameObject * parent);
	void SpawnGameObjectFromFile( nlohmann::json j);
	void DestroyGameObject(GameObject * gObject);

	void UpdateGameObjects(double deltaTime);
	void RenderGameObjects();
	void CleanUpGameObjects();

	GameObject* GetActiveCamera() { return m_activeCamera; }
	void RegisterCamera(Component * cameraComp);

	void UpdateCameraObjects(double deltaTime);
};

#endif