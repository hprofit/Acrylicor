/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShakeEvent.h
Purpose: Event that indicates a camera shake should happen and for how long
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/08/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SHAKE_EVENT_H
#define SHAKE_EVENT_H

#include "AcryEvent.h"
#include "Contact.h"

class GameObject;

class ShakeEvent :
	public AcryEvent
{
private:
	double duration;

public:
	ShakeEvent(double _duration);
	virtual ~ShakeEvent();

	double Duration() { return duration; }
};

#endif
