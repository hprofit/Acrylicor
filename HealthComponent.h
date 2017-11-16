/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HealthComponent.h
Purpose: Base HealthComponent class that contains HitPoints
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "Component.h"

class HealthComponent : 
	public Component
{
protected:
	int m_hitPoints;
public:
	HealthComponent() = delete;
	HealthComponent(GameObject& parent);
	HealthComponent(GameObject& parent, int hitPoints);
	HealthComponent(const HealthComponent& rhs, GameObject& parent);
	virtual ~HealthComponent();

	virtual void Update(double deltaTime);
	virtual HealthComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
};
#endif
