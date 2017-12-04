/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PickupEvent.h
Purpose: Indicates a pickup was retrieved by the player
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PICKUP_EVENT_H
#define PICKUP_EVENT_H

#include "AcryEvent.h"
#include "PickupTypes.h"

class PickupEvent :
	public AcryEvent
{
private:
	PICKUP_TYPE pickup;

public:
	PickupEvent(PICKUP_TYPE _pickup);
	virtual ~PickupEvent();

	PICKUP_TYPE PickupType() const { return pickup; }
};

#endif
