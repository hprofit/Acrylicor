/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PickupComponent.h
Purpose: Provides pickup logic for a game object
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/20/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PICKUP_COMPONENT_H
#define PICKUP_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"
#include "PickupTypes.h"

class PickupComponent :
	public Component
{
protected:
	PICKUP_TYPE m_pickupType;

public:
	PickupComponent() = delete;
	PickupComponent(GameObject& parent);
	PickupComponent(const PickupComponent& rhs, GameObject& parent);
	virtual ~PickupComponent();

	virtual void Update(double deltaTime);
	virtual PickupComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
};

#endif
