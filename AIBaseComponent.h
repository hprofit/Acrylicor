/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AIBaseComponent.h
Purpose: Base AI component
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/05/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef AI_BASE_COMPONENT_H
#define AI_BASE_COMPONENT_H

#include "Component.h"

class AIBaseComponent :
	public Component
{
protected:
	bool m_active;

	AIBaseComponent(COMPONENT_TYPE type, GameObject& parent);
	AIBaseComponent(COMPONENT_TYPE type, const AIBaseComponent& rhs, GameObject& parent);
public:
	AIBaseComponent() = delete;
	virtual ~AIBaseComponent();

	virtual void Activate();
	virtual void Deactivate();
};

#endif
