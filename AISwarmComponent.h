/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AISwarmComponent.h
Purpose: Simple AI that swarm with other AIs of the same type
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_SWARM_COMPONENT_H
#define AI_SWARM_COMPONENT_H

#include "AcrylicorTypedefs.h"
#include "AIBaseComponent.h"
#include "Vector3D.h"
#include <vector>

class TransformComponent;
class PhysicsComponent;
class GameObject;

class AISwarmComponent :
	public AIBaseComponent
{
private:
	float m_speed;
	float m_maxTurnSpeed;
	float m_viewDistance;
	float m_viewDistanceSq;

	GameObject* m_target;
	TransformComponent* m_targetTComp;
	String m_tagToFind;

	float m_cohWeight;
	float m_sepWeight;
	float m_aliWeight;
	float m_seekWeight;

	TransformComponent* m_tComp;
	PhysicsComponent* m_pComp;

	std::vector<TransformComponent*> m_neighbors;

	void _CalculateSwarmMovement(double deltaTime);

	void _FindNeighbors();
public:
	AISwarmComponent() = delete;
	AISwarmComponent(GameObject& parent, float viewDistance, float maxTurnSpeed, float speed, float cohWeight = 1.f, float sepWeight = 1.f, float aliWeight = 1.f, float seekWeight = 1.f);
	AISwarmComponent(const AISwarmComponent& rhs) = delete;
	AISwarmComponent(const AISwarmComponent& rhs, GameObject& parent);
	AISwarmComponent& operator= (AISwarmComponent rhs) = delete;
	~AISwarmComponent();

	virtual void Update(double deltaTime);
	virtual AISwarmComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent* aEvent);
	virtual void LateInitialize();
};

#endif