/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MissileAddedEvent.h
Purpose: Event containing an amount of missiles to be added to player inventory
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MISSILE_ADDED_EVENT_H
#define MISSILE_ADDED_EVENT_H

#include "AcryEvent.h"

class MissileAddedEvent :
	public AcryEvent
{
private:
	int missileAmt;
public:
	MissileAddedEvent(int _missileAmt);
	virtual ~MissileAddedEvent();

	int Amount() { return missileAmt; }
};

#endif