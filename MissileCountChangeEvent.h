/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MissileCountChangeEvent.h
Purpose: Event that indicates the amount of missiles set all containers to
I.e. UI will now be exactly this many missiles, missile launcher will be this many missiles
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MISSILE_COUNT_CHANGE_EVENT_H
#define MISSILE_COUNT_CHANGE_EVENT_H

#include "AcryEvent.h"

class MissileCountChangeEvent :
	public AcryEvent
{
private:
	int count;
public:
	MissileCountChangeEvent(double time, int _count);
	~MissileCountChangeEvent();

	int Count() const;
};

#endif