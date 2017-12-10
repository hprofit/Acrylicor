/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScoreComponent.h
Purpose: Handles adds to player score when Score event is received
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SCORE_COMPONENT_H
#define SCORE_COMPONENT_H

#include "Component.h"

class ScoreComponent :
	public Component
{
protected:
	int m_scoreValue;

public:
	ScoreComponent() = delete;
	ScoreComponent(GameObject& parent, int scoreValue);
	ScoreComponent(const ScoreComponent& rhs, GameObject& parent);
	virtual ~ScoreComponent();

	virtual void Update(double deltaTime);
	virtual ScoreComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);

	int Score() const { return m_scoreValue; }
};

#endif
