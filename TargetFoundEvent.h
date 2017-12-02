/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TargetFoundEvent.h
Purpose: Event that indicates a specified target object has been found
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/01/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef TARGET_FOUND_EVENT_H
#define TARGET_FOUND_EVENT_H

#include "AcryEvent.h"
#include "Contact.h"

class GameObject;

class TargetFoundEvent :
	public AcryEvent
{
private:
	GameObject* m_target;

public:
	TargetFoundEvent(GameObject* target);
	virtual ~TargetFoundEvent();

	GameObject* GetTarget() { return m_target; }
};

#endif
