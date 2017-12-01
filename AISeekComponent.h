/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AISeekComponent.h
Purpose: AI that will examine the surrounding vicinity for objects with a given tag
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_SEEK_COMPONENT_H
#define AI_SEEK_COMPONENT_H

#include "AcrylicorTypedefs.h"
#include "Component.h"

class TransformComponent;

class AISeekComponent :
	public Component
{
protected:
	GameObject* m_target;
	TransformComponent* m_targetTComp;
	String m_tagToFind;
	float m_maxTurnSpeed;
	float m_speed;

	TransformComponent* m_tComp;

	void _FindNewTarget();
	void _SeekTarget(double deltaTime);
public:
	AISeekComponent() = delete;
	AISeekComponent(GameObject& parent, String tagToFind, float maxTurnSpeed, float speed);
	AISeekComponent(const AISeekComponent& rhs) = delete;
	AISeekComponent(const AISeekComponent& rhs, GameObject& parent);
	AISeekComponent& operator= (AISeekComponent rhs) = delete;
	~AISeekComponent();

	virtual void Update(double deltaTime);
	virtual AISeekComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();
};



#endif