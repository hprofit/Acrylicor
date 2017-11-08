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
Creation date: 10/20/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "GameObject.h"
#include "json.hpp"
#include "AcrylicorTypedefs.h"

using json = nlohmann::json;

class GameObjectManager;

class GameObjectFactory
{
private:
	std::map<String, GameObject * > m_gameObjectTypes;

	GameObjectFactory();
	~GameObjectFactory();

	GameObject * SpawnObjectWithOverrides(String objectType, json j);
	/*!
	Returns the archetype instance of the specified game object.
	*/
	GameObject * GetObjectArchetype(String objectType);

public:
	GameObjectFactory(const GameObjectFactory&) = delete;
	void operator=(const GameObjectFactory&) = delete;

	friend GameObjectManager;

	static GameObjectFactory& GetInstance()
	{
		static GameObjectFactory instance;
		return instance;
	}

	/*!
	Returns a new instance of the specified game object archetype
	*/
	GameObject * NewObjectFromArchetype(String objectType);

	GameObject * LoadGameObjectFromFile(String fileName);
	void LoadGameObjectsFromFile(String fileName);
};

#endif