/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UI_MissilesComponent.h
Purpose: A UI component that displays remaining missiles
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

class UI_MissilesComponent :
	public Component
{
protected:
	int m_count;
	String m_baseMessage;

public:
	UI_MissilesComponent() = delete;
	UI_MissilesComponent(GameObject& parent, String baseMessage);
	UI_MissilesComponent(const UI_MissilesComponent& rhs) = delete;
	UI_MissilesComponent(const UI_MissilesComponent& rhs, GameObject& parent);
	UI_MissilesComponent& operator= (UI_MissilesComponent rhs) = delete;
	~UI_MissilesComponent();

	virtual void Update(double deltaTime);
	virtual UI_MissilesComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);

	void AddMissile();
	void AddMissiles(int amt);
	void RemoveMissile();
	void RemoveMissiles(int amt);
};

#endif