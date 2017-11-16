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

#include "AcrylicorTypedefs.h"
#include "ComponentTypes.h"
#include "Component.h"
#include <map>
#include <vector>

const unsigned char FLAG_ACTIVE = 0x1;
const unsigned char FLAG_READY_TO_DIE = 0x2;

class AcryEvent;
class GameObjectManager;

class GameObject
{
protected:
	String m_type;
	GameObject * m_parent;
	std::vector<GameObject *> m_children;
	
	unsigned char m_objectFlags;
	std::map<COMPONENT_TYPE, Component*> m_components;

	void CloneChildren(const GameObject & rhs);

public:
	friend GameObjectManager;

	GameObject(String type);
	GameObject(const GameObject & rhs);
	GameObject(const GameObject & rhs, GameObject * parent);
	GameObject& operator=(const GameObject & rhs);
	virtual ~GameObject();

	virtual void ResetFlags();
	virtual void Activate();
	virtual void Deactivate();
	virtual bool IsActive();
	virtual void Kill();
	virtual bool IsDead();

	void SetParent(GameObject * parent);
	void AddChild(GameObject * child);
	bool HasParent() const {
		return m_parent != nullptr;
	}
	bool HasChildren() const {
		return m_children.size() != 0;
	}
	GameObject * Parent() const {
		return m_parent;
	}
	GameObject * GetChildOfType(String type) const;

	bool Has(COMPONENT_TYPE type);
	Component* Get(COMPONENT_TYPE type);
	Component* GetImmediate(COMPONENT_TYPE type);
	void AddComponent(Component * component);
	void ClearComponents();

	virtual void Update(double deltaTime);

	void HandleEvent(AcryEvent * aEvent);
};

#endif