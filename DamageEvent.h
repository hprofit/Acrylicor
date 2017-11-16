/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DamageEvent.h
Purpose: Event containing damage amount to be applied to a game object
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef DAMAGE_EVENT_H
#define DAMAGE_EVENT_H

#include "AcryEvent.h"

class DamageEvent :
	public AcryEvent
{
private:
	int damageAmt;
public:
	DamageEvent(double time, int dmgAmt);
	virtual ~DamageEvent();

	int Amount() { return damageAmt; }
};

#endif