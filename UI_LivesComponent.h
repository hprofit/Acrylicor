/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UI_LivesComponent.h
Purpose: A UI component that displays remaining player lives
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef UI_LIVES_COMPONENT_H
#define UI_LIVES_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

class UI_LivesComponent : 
	public Component
{
protected:
	int m_lives;
	float m_scaleX;
	float m_scaleY;

public:
	UI_LivesComponent() = delete;
	UI_LivesComponent(GameObject& parent, float scaleX, float scaleY, int lives = 3);
	UI_LivesComponent(const UI_LivesComponent& rhs) = delete;
	UI_LivesComponent(const UI_LivesComponent& rhs, GameObject& parent);
	UI_LivesComponent& operator= (UI_LivesComponent rhs) = delete;
	~UI_LivesComponent();

	virtual void Update(double deltaTime);
	virtual UI_LivesComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);

	void AddLife();
	void AddLives(int amt);
	void RemoveLife();
	void RemoveLives(int amt);
};

#endif