/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UI_MainMenuComponent.h
Purpose: A UI component that displays the main menu and handles selection of options
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/16/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef UI_MAIN_MENU_COMPONENT_H
#define UI_MAIN_MENU_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"
#include <vector>

class TextComponent;

class UI_MainMenuComponent :
	public Component
{
protected:
	enum class MENU_OPTION {
		START = 0,
		EXIT
	};
	String m_baseMessage;

	std::vector<TextComponent*> m_teComp;

	void _SetText() const;
public:
	UI_MainMenuComponent() = delete;
	UI_MainMenuComponent(GameObject& parent, String baseMessage);
	UI_MainMenuComponent(const UI_MainMenuComponent& rhs) = delete;
	UI_MainMenuComponent(const UI_MainMenuComponent& rhs, GameObject& parent);
	UI_MainMenuComponent& operator= (UI_MainMenuComponent rhs) = delete;
	~UI_MainMenuComponent();

	virtual void Update(double deltaTime);
	virtual UI_MainMenuComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
	virtual void LateInitialize();
};

#endif