/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ControllerComponent.h
Purpose: Handles default input
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/20/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H

#include "Component.h"

class ControllerComponent :
	public Component
{
public:
	ControllerComponent() = delete;
	ControllerComponent(GameObject& parent);
	ControllerComponent(const ControllerComponent& rhs, GameObject& parent);
	virtual ~ControllerComponent();

	virtual void Update(double deltaTime);
	virtual ControllerComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
};

#endif
