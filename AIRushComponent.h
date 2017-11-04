/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AIRushComponent.h
Purpose: Simple AI that will move in the indicated direction.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_RUSH_COMPONENT_H
#define AI_RUSH_COMPONENT_H

#include "Component.h"

class AIRushComponent :
	public Component
{
protected:
	enum {
		FORWARD = 0
	};

	unsigned short m_moveType;
	float m_speed;
public:
	AIRushComponent() = delete;
	AIRushComponent(GameObject& parent, unsigned short moveType, float speed);
	AIRushComponent(const AIRushComponent& rhs) = delete;
	AIRushComponent(const AIRushComponent& rhs, GameObject& parent);
	AIRushComponent& operator= (AIRushComponent rhs) = delete;
	~AIRushComponent();

	virtual void Update(double deltaTime);
	virtual AIRushComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
};


#endif