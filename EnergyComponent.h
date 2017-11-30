/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnergyComponent.h
Purpose: Base EnergyComponent class that contains Energy Points
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef ENERGY_COMPONENT_H
#define ENERGY_COMPONENT_H

#include "Component.h"

class EnergyComponent :
	public Component
{
protected:
	float m_energy;
	float m_maxEnergy;
	float m_rechargeRate;
public:
	EnergyComponent() = delete;
	EnergyComponent(GameObject& parent, float maxEnergy, float rechargeRate);
	EnergyComponent(const EnergyComponent& rhs, GameObject& parent);
	virtual ~EnergyComponent();

	virtual void Update(double deltaTime);
	virtual EnergyComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();

	bool EnoughEnergy(float energyRequired) const;
	void UseEnergy(float amount);
};
#endif
