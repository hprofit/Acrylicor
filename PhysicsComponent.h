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
	bool m_weightless;
	float m_maxSpeed;
	float m_capRate;
	PhysicsBody * m_body;
	bool m_static;
public:
	PhysicsComponent(GameObject& parent);
	PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity);
	PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity, Vector3D acceleration);
	PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float invMass, bool weightless, float maxSpeed, float capRate);
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
	virtual void HandleEvent(AcryEvent * aEvent);

	void AddForce(Vector3D force);
	void SetVelocity(Vector3D vel);
	void InterpolateVelocity(Vector3D vel, float weight);
	PhysicsBody& Body() const { return *m_body; };
	PhysicsBody* GetBodyPtr() const { return m_body; }
	Vector3D GetPosition() const { return m_position; };
	void SetPosition(Vector3D position);
	Vector3D GetPrevPosition() const { return m_prevPosition; };
	void SetPrevPosition(Vector3D position);
	bool IsStatic() const;
};

#endif