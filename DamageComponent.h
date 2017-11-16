/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DamageComponent.h
Purpose: Base DamageComponent class that contains damage to be received when contact 
is made with this component's parent GameObject
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#include "Component.h"

class DamageComponent :
	public Component
{
protected:
	int m_damage;
public:
	DamageComponent() = delete;
	DamageComponent(GameObject& parent, int damage);
	DamageComponent(const DamageComponent& rhs, GameObject& parent);
	virtual ~DamageComponent();

	virtual void Update(double deltaTime);
	virtual DamageComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);

	int Amount() const { return m_damage; }
};
#endif
