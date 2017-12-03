/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: KeyReleasedEvent.h
Purpose: Event that indicates a specific key was released.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/01/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef KEY_RELEASED_EVENT_H
#define KEY_RELEASED_EVENT_H

#include "AcryEvent.h"
#include "SDL_keycode.h"

class KeyReleasedEvent :
	public AcryEvent
{
private:
	Uint8 m_keyCode;

public:
	KeyReleasedEvent(double time, Uint8 keyCode);
	~KeyReleasedEvent();

	Uint8 GetKey() { return m_keyCode; }
};

#endif