/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AISwayComponent.h
Purpose: Simple AI that will gently sway the parent GameObject side to side
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_SWAY_COMPONENT_H
#define AI_SWAY_COMPONENT_H

#include "AIBaseComponent.h"
#include "AcrylicorTypedefs.h"

class AISwayComponent :
	public AIBaseComponent
{
private:
	float m_swayAmount;
	float m_currX;
	float m_direction;
	float m_speed;

public:
	AISwayComponent() = delete;
	AISwayComponent(GameObject& parent, float swayAmount, float speed = 1.f);
	AISwayComponent(const AISwayComponent& rhs) = delete;
	AISwayComponent(const AISwayComponent& rhs, GameObject& parent);
	AISwayComponent& operator= (AISwayComponent rhs) = delete;
	~AISwayComponent();

	virtual void Update(double deltaTime);
	virtual AISwayComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
};

#endif