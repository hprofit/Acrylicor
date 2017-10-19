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

class GameObject;
//#include "GameObject.h"

class Component
{
public:
	GameObject& m_parent;

	Component(GameObject& parent) : m_parent(parent) {};
	Component(Component const& rhs) = delete;
	Component& operator= (Component rhs) = delete;
	~Component() {};

};
#endif
