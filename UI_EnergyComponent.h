/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UI_EnergyComponent.h
Purpose: A UI component that displays remaining energy
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef UI_ENERGY_COMPONENT_H
#define UI_ENERGY_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

class UI_EnergyComponent :
	public Component
{
protected:
	int m_energy;
	String m_baseMessage;

	void _SetText() const;
public:
	UI_EnergyComponent() = delete;
	UI_EnergyComponent(GameObject& parent, String baseMessage);
	UI_EnergyComponent(const UI_EnergyComponent& rhs) = delete;
	UI_EnergyComponent(const UI_EnergyComponent& rhs, GameObject& parent);
	UI_EnergyComponent& operator= (UI_EnergyComponent rhs) = delete;
	~UI_EnergyComponent();

	virtual void Update(double deltaTime);
	virtual UI_EnergyComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();
};

#endif