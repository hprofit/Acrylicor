/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: Base GameObject class
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "ComponentTypes.h"
#include "Component.h"
#include <map>

#define FLAG_ACTIVE	0x00000001

class GameObject
{
protected:
	unsigned long m_active;
	std::map<COMPONENT_TYPE, Component*> m_components;

public:
	GameObject();
	GameObject(GameObject const& rhs);
	virtual ~GameObject();

	virtual void Activate();
	virtual void Deactivate();
	virtual unsigned long GetActive();

	bool Has(COMPONENT_TYPE type);
	Component* Get(COMPONENT_TYPE type);
	void AddComponent(Component * component);

	virtual void Update(double deltaTime);
};

#endif