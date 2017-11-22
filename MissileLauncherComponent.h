/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MissileLauncherComponent.h
Purpose: Missile launcher component for launching different types of 
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/20/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MISSILE_LAUNCHER_COMPONENT_H
#define MISSILE_LAUNCHER_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

class MissileLauncherComponent :
	public Component
{
protected:
	int m_count;
	double m_rateOfFire;
	double m_timeSinceLastFired;
	String m_missileType;	// Type of missile to call GameObjectManager to spawn

public:
	MissileLauncherComponent(GameObject & parent, int count, double rateOfFire, String missileType);
	MissileLauncherComponent& operator=(MissileLauncherComponent rhs) = delete;
	MissileLauncherComponent(const MissileLauncherComponent& rhs) = delete;
	MissileLauncherComponent(const MissileLauncherComponent& rhs, GameObject& parent);
	~MissileLauncherComponent();

	virtual void Update(double deltaTime);
	virtual MissileLauncherComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();

	int Remaining() const;
	void Fire();
};

#endif
