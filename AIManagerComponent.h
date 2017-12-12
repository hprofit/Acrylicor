/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AIManagerComponent.h
Purpose: AI that will activate certain AI components when the AI is close enough to being on screen
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/11/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_MANAGER_COMPONENT_H
#define AI_MANAGER_COMPONENT_H

#include "AIBaseComponent.h"
#include "AcrylicorTypedefs.h"
#include <vector>

class TransformComponent;

class AIManagerComponent :
	public AIBaseComponent
{
protected:
	float m_range;
	std::vector<String> m_aiComponentTypesToActivate;
	std::vector<String> m_aiComponentTypesToDeactivate;
	std::vector<AIBaseComponent*> m_aiComponentsToActivate;
	std::vector<AIBaseComponent*> m_aiComponentsToDeactivate;

	TransformComponent* m_tComp;

	void _AcivateAIComponents();
	void _DeactivateAIComponents();
public:
	AIManagerComponent() = delete;
	AIManagerComponent(GameObject& parent, float range = 500.f);
	AIManagerComponent(const AIManagerComponent& rhs) = delete;
	AIManagerComponent(const AIManagerComponent& rhs, GameObject& parent);
	AIManagerComponent& operator= (AIManagerComponent rhs) = delete;
	~AIManagerComponent();

	virtual void Update(double deltaTime);
	virtual AIManagerComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void LateInitialize();
};


#endif