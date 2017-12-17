/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AISpawnOnDeathComponent.h
Purpose: AI that calls SpawnerComponent to spawn when this GO is destroyed
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/10/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_SPAWN_ON_DEATH_COMPONENT_H
#define AI_SPAWN_ON_DEATH_COMPONENT_H

#include "AIBaseComponent.h"

class SpawnerComponent;

class AISpawnOnDeathComponent :
	public AIBaseComponent
{
protected:
	int m_amount;

	SpawnerComponent* m_sComp;
public:
	AISpawnOnDeathComponent() = delete;
	AISpawnOnDeathComponent(GameObject& parent, int amount);
	AISpawnOnDeathComponent(const AISpawnOnDeathComponent& rhs) = delete;
	AISpawnOnDeathComponent(const AISpawnOnDeathComponent& rhs, GameObject& parent);
	AISpawnOnDeathComponent& operator= (AISpawnOnDeathComponent rhs) = delete;
	~AISpawnOnDeathComponent();

	virtual void Update(double deltaTime);
	virtual AISpawnOnDeathComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();
};


#endif