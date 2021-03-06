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

#include "AcrylicorTypedefs.h"
#include "Vector3D.h"
#include "Rect3D.h"
#include <math.h>
#include <list>
#include "Tags.h"

enum BODY_TYPE {
	BT_CIRCLE = 0,
	BT_AABB,

	NUM
};

class PhysicsBody
{
protected:
	Tags m_tags;

	PhysicsBody(BODY_TYPE type);
	PhysicsBody(const PhysicsBody& rhs);
public:
	const BODY_TYPE m_type;

	PhysicsBody() = delete;
	virtual ~PhysicsBody() {};
	Tags& Tags();
};

class Circle : 
	public PhysicsBody {
public:
	float m_radius;

	Circle() : PhysicsBody(BODY_TYPE::BT_CIRCLE), m_radius(0.f) {};
	Circle(float radius) : PhysicsBody(BODY_TYPE::BT_CIRCLE), m_radius(radius) {};
	Circle(const Circle& rhs) : PhysicsBody(rhs), m_radius(rhs.m_radius) {};
	Circle& operator=(const Circle& rhs) {
		m_radius = rhs.m_radius;
	};
	virtual ~Circle() {}
};

class AABB : 
	public PhysicsBody {
public:
	float m_width;
	float m_halfWidth;
	float m_height;
	float m_halfHeight;
	float m_diagonal;
	Rect3D m_rect;

	AABB() : 
		PhysicsBody(BODY_TYPE::BT_AABB),
		m_width(0.f), m_halfWidth(0.f), 
		m_height(0.f), m_halfHeight(0.f), 
		m_diagonal(0.f),
		m_rect(Rect3D(Vector3D(), m_halfWidth, m_halfHeight))
	{}

	AABB(float dim) : 
		PhysicsBody(BODY_TYPE::BT_AABB),
		m_width(dim), m_halfWidth(dim / 2.f), 
		m_height(dim), m_halfHeight(dim / 2.f), 
		m_diagonal(  sqrtf(((dim / 2.f) * (dim / 2.f)) + ((dim / 2.f) * (dim / 2.f))) ),
		m_rect(Rect3D(Vector3D(), m_halfWidth, m_halfHeight))
	{}

	AABB(float width, float height) : 
		PhysicsBody(BODY_TYPE::BT_AABB),
		m_width(width), m_halfWidth(width / 2.f), 
		m_height(height), m_halfHeight(height / 2.f), 
		m_diagonal( sqrtf(((width / 2.f) * (width / 2.f)) + ((height / 2.f) * (height / 2.f))) ),
		m_rect(Rect3D(Vector3D(), m_halfWidth, m_halfHeight))
	{}

	AABB(const AABB& rhs) : 
		PhysicsBody(rhs),
		m_width(rhs.m_width), m_halfWidth(rhs.m_halfWidth),
		m_height(rhs.m_height), m_halfHeight(rhs.m_halfHeight),
		m_diagonal(rhs.m_diagonal),
		m_rect(rhs.m_rect) {}

	AABB& operator=(const AABB& rhs) {
		m_width = rhs.m_width;
		m_halfWidth = rhs.m_halfWidth;
		m_height = rhs.m_height;
		m_halfHeight = rhs.m_halfHeight;
		m_diagonal = rhs.m_diagonal;
		m_rect = rhs.m_rect;
	};

	virtual ~AABB() {}
};

#endif