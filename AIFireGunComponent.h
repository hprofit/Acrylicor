/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AIFireGunComponent.h
Purpose: AI that will fire an attached WeaponComponent at a set interval.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/07/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_FIRE_GUN_COMPONENT_H
#define AI_FIRE_GUN_COMPONENT_H

#include "AIBaseComponent.h"

class WeaponComponent;

class AIFireGunComponent :
	public AIBaseComponent
{
protected:
	WeaponComponent* m_wComp;

	float m_fireFrequency;
	float m_timeSinceLastFire;
public:
	AIFireGunComponent() = delete;
	AIFireGunComponent(GameObject& parent, float fireFrequency);
	AIFireGunComponent(const AIFireGunComponent& rhs) = delete;
	AIFireGunComponent(const AIFireGunComponent& rhs, GameObject& parent);
	AIFireGunComponent& operator= (AIFireGunComponent rhs) = delete;
	~AIFireGunComponent();

	virtual void Update(double deltaTime);
	virtual AIFireGunComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void LateInitialize();
};


#endif