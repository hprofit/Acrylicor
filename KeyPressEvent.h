/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: KeyPressEvent.h
Purpose: Event that indicates a specific key was pressed.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef KEY_PRESS_EVENT_H
#define KEY_PRESS_EVENT_H

#include "AcryEvent.h"
#include "SDL_keycode.h"

class KeyPressEvent :
	public AcryEvent
{
private:
	Uint8 m_keyCode;

public:
	KeyPressEvent(unsigned int time, Uint8 keyCode) : 
		AcryEvent(time),
		m_keyCode(keyCode) {};
	~KeyPressEvent();

	Uint8 GetKey() { return m_keyCode; }
	virtual void Process();
};

#endif