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
#include "PhysicsComponent.h"
#include "Contact.h"
#include <map>
#include <string>
#include <vector>

class PhysicsManager
{
private:
	std::vector<Component *> m_physicsBodies;
	std::vector<Component *> m_transforms;
	std::vector<Contact *> m_contacts;

	std::vector< std::vector< bool(*)(PhysicsBody & lhs, Vector3D lhsPos, PhysicsBody & rhs, Vector3D rhsPos) > > m_collisionFunctions;

	PhysicsManager();
	~PhysicsManager();

	void RemoveBody(Component * comp);
	void RemoveTransform(Component * comp);

	void CreateContact(PhysicsBody* lhs, PhysicsBody* rhs);
	void ResetContacts();
	bool CheckCollision(PhysicsBody & lhs, Vector3D lhsPos, PhysicsBody & rhs, Vector3D rhsPos);

public:
	PhysicsManager(const PhysicsManager &) = delete;
	void operator=(const PhysicsManager &) = delete;

	static PhysicsManager& GetInstance()
	{
		static PhysicsManager instance;
		return instance;
	}

	void AddComponent(Component * comp);
	void RemoveComponent(Component * comp);

	void UpdatePhysics(double deltaTime);
};

#endif