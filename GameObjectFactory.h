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

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "GameObject.h"
#include "Component.h"


#include "TransformComponent.h"
#include "ControllerComponent.h"
#include "SpriteComponent.h"
#include "PhysicsBodyComponent.h"
#include "PhysicsMovementComponent.h"
#include "json.hpp"
#include "AcrylicorTypedefs.h"

using json = nlohmann::json;

class GameObjectFactory
{
private:
	std::map<String, GameObject> m_gameObjectTypes;
	std::map<String, Component * > m_components;

	GameObjectFactory();
	~GameObjectFactory();

	TransformComponent * LoadTransformComponent(GameObject* gObject, const json j);
	SpriteComponent * LoadSpriteComponent(GameObject* gObject, const json j);
	ControllerComponent * LoadControllerComponent(GameObject* gObject, const json j);
	PhysicsBodyComponent * LoadPhysicsBodyComponent(GameObject* gObject, const json j);
	PhysicsMovementComponent * LoadPhysicsMovementComponent(GameObject* gObject, const json j);
public:
	GameObjectFactory(GameObjectFactory const&) = delete;
	void operator=(GameObjectFactory const&) = delete;

	static GameObjectFactory& GetInstance()
	{
		static GameObjectFactory instance;
		return instance;
	}

	void AddComponentType(String componentType, Component * component);

	GameObject * SpawnObject(String objectType);

	GameObject * LoadGameObjectFromFile(String fileName);
	void LoadGameObjectsFromFile(String fileName);

	void LoadLevelFile(String fileName);
};

#endif