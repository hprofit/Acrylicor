/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsMovementComponent.h
Purpose: Physics Movement Component class - contains velocity and acceleration
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PHYSICS_MOVEMENT_COMPONENT_H
#define PHYSICS_MOVEMENT_COMPONENT_H

#include "Component.h"
#include "Vector2D.h"

class PhysicsMovementComponent :
	public Component
{
private:
	Vector2D m_velocity, m_acceleration;
public:
	PhysicsMovementComponent(GameObject& parent);
	PhysicsMovementComponent(GameObject& parent, Vector2D velocity);
	PhysicsMovementComponent(GameObject& parent, Vector2D velocity, Vector2D acceleration);
	PhysicsMovementComponent(PhysicsMovementComponent const& rhs) = delete;
	PhysicsMovementComponent& operator= (PhysicsMovementComponent rhs) = delete;
	~PhysicsMovementComponent();
};

#endif