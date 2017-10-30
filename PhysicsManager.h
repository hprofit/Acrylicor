/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsManager.h
Purpose: Provides all physics functionality.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/27/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "AcrylicorTypedefs.h"
#include "GameObject.h"
#include "PhysicsBodyComponent.h"
#include "PhysicsMovementComponent.h"
#include <map>
#include <string>
#include <vector>

class PhysicsManager
{
private:
	std::vector<Component *> m_physicsComponents;

	PhysicsManager();
	~PhysicsManager();

public:
	PhysicsManager(PhysicsManager const&) = delete;
	void operator=(PhysicsManager const&) = delete;

	static PhysicsManager& GetInstance()
	{
		static PhysicsManager instance;
		return instance;
	}

	void AddComponent(Component * comp);
	void RemoveComponent(Component * comp);
};

#endif