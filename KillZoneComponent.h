/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: KillZoneComponent.h
Purpose: Kill Zone Component class - contains tags to handle what objects it should kill when a collision occurs
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef KILL_ZONE_COMPONENT_H
#define KILL_ZONE_COMPONENT_H

#include "Component.h"
#include <list>

class KillZoneComponent :
	public Component
{
protected:
	std::list<String> m_tags;
public:
	KillZoneComponent(GameObject& parent);
	KillZoneComponent& operator=(KillZoneComponent rhs) = delete;
	KillZoneComponent(const KillZoneComponent& rhs) = delete;
	KillZoneComponent(const KillZoneComponent& rhs, GameObject& parent);
	~KillZoneComponent();

	virtual void Update(double deltaTime);
	virtual KillZoneComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);

	void AddTag(String tag);
	bool HasTag(String tag) const;
	void RemoveTag(String tag);
	void SetTags(std::list<String> tags);
};

#endif