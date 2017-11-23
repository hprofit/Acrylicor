/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollideKillZoneEvent.h
Purpose: Specialized collide event for kill zones
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/17/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GO_DESTROYED_EVENT_H
#define GO_DESTROYED_EVENT_H

#include "AcryEvent.h"

class GameObject;

class GODestroyedEvent :
	public AcryEvent
{
private:
	GameObject * gameObject;

public:
	GODestroyedEvent(double time, GameObject * go);
	virtual ~GODestroyedEvent();

	GameObject* GO() { return gameObject; }
};

#endif