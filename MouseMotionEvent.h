/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MouseMotionEvent.h
Purpose: Event that indicates a the mouse was moved and how much.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/01/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef MOUSE_MOTION_EVENT_H
#define MOUSE_MOTION_EVENT_H

#include "AcryEvent.h"
#include "SDL_keycode.h"

class MouseMotionEvent :
	public AcryEvent
{
private:

public:
	MouseMotionEvent(double time);
	~MouseMotionEvent();

};

#endif