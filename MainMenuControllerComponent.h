/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenuControllerComponent.h
Purpose: Handles main menu input
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/16/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MAIN_MENU_CONTROLLER_COMPONENT_H
#define MAIN_MENU_CONTROLLER_COMPONENT_H

#include "Component.h"

class MainMenuControllerComponent :
	public Component
{
public:
	MainMenuControllerComponent() = delete;
	MainMenuControllerComponent(GameObject& parent);
	MainMenuControllerComponent(const MainMenuControllerComponent& rhs, GameObject& parent);
	virtual ~MainMenuControllerComponent();

	virtual void Update(double deltaTime);
	virtual MainMenuControllerComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
};

#endif
