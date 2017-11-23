/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DashComponent.h
Purpose: Allows the GameObject a small burst of speed it's current direction
is made with this component's parent GameObject
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef DASH_COMPONENT_H
#define DASH_COMPONENT_H

#include "Component.h"

class PhysicsComponent;

class DashComponent :
	public Component
{
protected:
	int m_energyRequired;
	float m_speed;
	float m_maxSpeed;
	double m_dashTime;
	double m_currentDashTime;

	PhysicsComponent* m_pComp;

public:
	DashComponent() = delete;
	DashComponent(GameObject& parent, int energyRequired, float speed, double dashTime);
	DashComponent(const DashComponent& rhs, GameObject& parent);
	virtual ~DashComponent();

	virtual void Update(double deltaTime);
	virtual DashComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();
};
#endif
