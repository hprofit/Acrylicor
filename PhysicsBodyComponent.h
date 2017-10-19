/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsBodyComponent.h
Purpose: Physics Body Component class - contains contains a body type for collision purposes
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PHYSICS_BODY_COMPONENT_H
#define PHYSICS_BODY_COMPONENT_H

#include "Component.h"
#include "Vector2D.h"

struct Circle {
	float m_radius;
};

struct Rectangle {
	float m_width, m_height;
};

class PhysicsBodyComponent :
	public Component
{
public:
	PhysicsBodyComponent(GameObject& parent);
	~PhysicsBodyComponent();
};

#endif