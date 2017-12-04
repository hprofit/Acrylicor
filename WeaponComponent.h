/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: WeaponComponent.h
Purpose: A weapon component that contains logic for the spawning of various types of bullets
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/07/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef WEAPON_COMPONENT_H
#define WEAPON_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

enum class WeaponType {
	SINGLE_BARREL = 0,
	DOUBLE_BARREL,
	SPLIT_BARREL
};

class WeaponComponent :
	public Component
{
protected:
	WeaponType m_weaponType;
	double m_rateOfFire;
	String m_bulletType;	// Type of bullet to call GameObjectManager to spawn
	unsigned int m_burstAmount;
	double m_timeSinceLastFired;

	void _FireSingleBarrel();
	void _FireDoubleBarrel();
	void _FireSplitBarrel();
public:
	WeaponComponent() = delete;
	WeaponComponent(GameObject& parent, WeaponType weaponType, double rateOfFire, String bulletType, unsigned int burstAmount = 1);
	WeaponComponent(const WeaponComponent& rhs) = delete;
	WeaponComponent(const WeaponComponent& rhs, GameObject& parent);
	WeaponComponent& operator= (WeaponComponent rhs) = delete;
	~WeaponComponent();

	virtual void Update(double deltaTime);
	virtual WeaponComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);

	void Fire();
};

#endif