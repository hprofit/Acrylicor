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
#include "CollisionResult.h"
#include "Subscriber.h"
#include <map>
#include <string>
#include <vector>
#include <utility>

class EventManager;

class PhysicsManager : 
	public Subscriber
{
private:
	std::vector<Component *> m_physicsBodies;
	std::vector<Component *> m_transforms;
	std::vector<Contact *> m_contacts;

	EventManager& _EventManager;

	CollisionResult (* m_collisionFunctions[BODY_TYPE::NUM][BODY_TYPE::NUM] )(const PhysicsComponent &, Vector3D, Vector3D, const PhysicsComponent &, Vector3D, Vector3D);
	Vector3D (* m_reflectionFunctions[BODY_TYPE::NUM][BODY_TYPE::NUM])(const PhysicsComponent &, const PhysicsComponent &, const CollisionResult&);
	Vector3D(*m_pushFunctions[BODY_TYPE::NUM][BODY_TYPE::NUM])(const PhysicsComponent &, const PhysicsComponent &, const Vector3D &, const CollisionResult&);

	PhysicsManager();
	virtual ~PhysicsManager();

	void _RemoveBody(Component * comp);
	void _RemoveTransform(Component * comp);
	void _RemoveAll();

	void _CreateContact(GameObject* lhsGO, GameObject* rhsGO, CollisionResult collision);
	void _ResetContacts();
	CollisionResult _CheckCollision(const PhysicsComponent & lhs, const PhysicsComponent & rhs);

public:
	PhysicsManager(const PhysicsManager &) = delete;
	void operator=(const PhysicsManager &) = delete;

	static PhysicsManager& GetInstance()
	{
		static PhysicsManager instance;
		return instance;
	}

	virtual void HandleEvent(AcryEvent * aEvent);

	void AddComponent(Component * comp);
	void RemoveComponent(Component * comp);

	void UpdatePhysics(double deltaTime);

	Vector3D ReflectShapeOffOtherShape(const PhysicsComponent & lhs, const PhysicsComponent & rhs, const CollisionResult& cr);
	Vector3D PushShapeOutOfOtherShape(const PhysicsComponent & lhs, const PhysicsComponent & rhs, const Vector3D & poi, const CollisionResult& cr);
};

#endif