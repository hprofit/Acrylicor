/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UI_ScoreComponent.h
Purpose: A UI component that displays the current score
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef UI_SCORE_COMPONENT_H
#define UI_SCORE_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

class UI_ScoreComponent :
	public Component
{
protected:
	int m_score;
	String m_baseMessage;

	void _SetText() const;
public:
	UI_ScoreComponent() = delete;
	UI_ScoreComponent(GameObject& parent, String baseMessage);
	UI_ScoreComponent(const UI_ScoreComponent& rhs) = delete;
	UI_ScoreComponent(const UI_ScoreComponent& rhs, GameObject& parent);
	UI_ScoreComponent& operator= (UI_ScoreComponent rhs) = delete;
	~UI_ScoreComponent();

	virtual void Update(double deltaTime);
	virtual UI_ScoreComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();

	void AddScore(int amt);
	void RemoveScore(int amt);
	void SetScore(int amt);
};

#endif