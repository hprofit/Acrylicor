/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AIAreaOfSightComponent.h
Purpose: AI that will look for targets within a specific range and fire events when found
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_AREA_OF_SIGHT_COMPONENT_H
#define AI_AREA_OF_SIGHT_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

class TransformComponent;

class AIAreaOfSightComponent :
	public Component
{
private:
	String m_tagToFind;
	float m_searchRadius;
	float m_searchRadiusSq;
	bool m_foundTarget;

	TransformComponent* m_tComp;

	void _FindNewTarget();
public:
	AIAreaOfSightComponent() = delete;
	AIAreaOfSightComponent(GameObject& parent, String tagToFind, float searchRadius);
	AIAreaOfSightComponent(const AIAreaOfSightComponent& rhs) = delete;
	AIAreaOfSightComponent(const AIAreaOfSightComponent& rhs, GameObject& parent);
	AIAreaOfSightComponent& operator= (AIAreaOfSightComponent rhs) = delete;
	~AIAreaOfSightComponent();

	virtual void Update(double deltaTime);
	virtual AIAreaOfSightComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent* aEvent);
	virtual void LateInitialize();

	float GetSearchRadius() const { return m_searchRadius; };
};

#endif