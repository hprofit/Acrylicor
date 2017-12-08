/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AISquareSwayComponent.h
Purpose: AI that will move the object forward a set distance, then left, then forward, then right, then repeat.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/06/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_SQUARE_SWAY_COMPONENT_H
#define AI_SQUARE_SWAY_COMPONENT_H

#include "AIBaseComponent.h"

class TransformComponent;
class PhysicsComponent;

class AISquareSwayComponent :
	public AIBaseComponent
{
protected:
	enum {
		LEFT = 0,
		FORWARD,
		RIGHT
	};

	unsigned short m_currentDirection;
	unsigned short m_previousDirection;
	float m_speed;
	float m_verticalDistance;
	float m_horizontalDistance;

	float m_currentDistanceTravelled;

	TransformComponent* m_tComp;
	PhysicsComponent* m_pComp;

	void _HandleDirectionChange();
public:
	AISquareSwayComponent() = delete;
	AISquareSwayComponent(GameObject& parent, float speed, float verticalDistance, float horizontalDistance);
	AISquareSwayComponent(const AISquareSwayComponent& rhs) = delete;
	AISquareSwayComponent(const AISquareSwayComponent& rhs, GameObject& parent);
	AISquareSwayComponent& operator= (AISquareSwayComponent rhs) = delete;
	~AISquareSwayComponent();

	virtual void Update(double deltaTime);
	virtual AISquareSwayComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void LateInitialize();
};


#endif