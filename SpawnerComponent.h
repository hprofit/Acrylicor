/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpawnerComponent.h
Purpose: A spawn point component that calls GameObjectManager to create new GameObjects of a given Archetype.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SPAWNER_COMPONENT_H
#define SPAWNER_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

class TransformComponent;

class SpawnerComponent :
	public Component
{
protected:
	String m_objectType;

	TransformComponent* m_tComp;

	void _Spawn();
public:
	SpawnerComponent() = delete;
	SpawnerComponent(GameObject& parent, String objectType);
	SpawnerComponent(const SpawnerComponent& rhs) = delete;
	SpawnerComponent(const SpawnerComponent& rhs, GameObject& parent);
	SpawnerComponent& operator= (SpawnerComponent rhs) = delete;
	~SpawnerComponent();

	virtual void Update(double deltaTime);
	virtual SpawnerComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();

	void SpawnMultiple(unsigned int amount);
};

#endif