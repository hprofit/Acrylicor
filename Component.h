/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Component.h
Purpose: Base Component class
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "ComponentTypes.h"
#include "json.hpp"

class GameObject;

class Component
{
protected:
	Component(GameObject& parent, COMPONENT_TYPE type, bool priority = false) :
		m_parent(parent), m_type(type), m_priority(priority) {}

public:
	GameObject& m_parent;
	const COMPONENT_TYPE m_type;
	const bool m_priority;

	Component() = delete;
	Component(const Component & rhs) = delete;
	virtual ~Component() {};

	virtual void Update(double deltaTime) = 0;
	virtual Component* Clone(GameObject& parent) = 0;
	virtual void Override(nlohmann::json j) = 0;
	virtual void RegisterWithManager() = 0;

	bool IsPriorityComp() const { return m_priority; }
};
#endif
