/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsComponent.h
Purpose: Physics Component class - contains velocity, acceleration, and body data
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"
#include "Vector3D.h"
#include "PhysicsBody.h"

class PhysicsComponent :
	public Component
{
protected:
	Vector3D m_velocity;
	Vector3D m_acceleration;
	Vector3D m_position;
	Vector3D m_prevPosition;
	Vector3D m_force;
	float m_mass;
	float m_InvMass;
	PhysicsBody * m_body;
public:
	PhysicsComponent(GameObject& parent);
	PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity);
	PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity, Vector3D acceleration);
	PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float invMass);
	PhysicsComponent& operator=(PhysicsComponent rhs) = delete;
	PhysicsComponent(const PhysicsComponent& rhs) = delete;
	PhysicsComponent(const PhysicsComponent& rhs, GameObject& parent);
	~PhysicsComponent();

	virtual void Update(double deltaTime);
	virtual void Update(double deltaTime, float gravity);
	virtual PhysicsComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager();

	void AddForce(Vector3D force);
	PhysicsBody& Body() const { return *m_body; };
	Vector3D GetPosition() const { return m_position; };
	Vector3D GetPreviousPosition() const { return m_prevPosition; };
};

#endif