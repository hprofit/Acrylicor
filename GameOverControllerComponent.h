/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameOverControllerComponent.h
Purpose: Handles game over input
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAME_OVER_CONTROLLER_COMPONENT_H
#define GAME_OVER_CONTROLLER_COMPONENT_H

#include "Component.h"

class GameOverControllerComponent :
	public Component
{
public:
	GameOverControllerComponent() = delete;
	GameOverControllerComponent(GameObject& parent);
	GameOverControllerComponent(const GameOverControllerComponent& rhs, GameObject& parent);
	virtual ~GameOverControllerComponent();

	virtual void Update(double deltaTime);
	virtual GameOverControllerComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
};

#endif
