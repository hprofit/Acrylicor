/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsBody.h
Purpose: Physics Body class for collisions
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "Vector3D.h"

const int NUM_BODIES = 2;

enum BODY_TYPE {
	BT_CIRCLE = 0,
	BT_AABB
};

class PhysicsBody
{
protected:
public:
	const BODY_TYPE m_type;
	PhysicsBody(BODY_TYPE type) : m_type(type) {};
	virtual ~PhysicsBody();
};

class Circle : 
	public PhysicsBody {
protected:
	float m_radius;

public:
	Circle() : PhysicsBody(BT_CIRCLE), m_radius(0.f) {};
	Circle(float radius) : PhysicsBody(BT_CIRCLE), m_radius(radius) {};
	virtual ~Circle() {}
};

class AABB : 
	public PhysicsBody {
protected:
	float m_width;
	float m_height;

public:
	AABB() : PhysicsBody(BT_AABB), m_width(0.f), m_height(0.f) {}
	AABB(float dim) : PhysicsBody(BT_AABB), m_width(dim), m_height(dim) {}
	AABB(float width, float height) : PhysicsBody(BT_AABB), m_width(width), m_height(height) {}
	virtual ~AABB() {}
};

#endif