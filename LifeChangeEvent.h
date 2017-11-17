/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LifeChangeEvent.h
Purpose: Event that indicates a gain or decrease in player lives and how many
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/15/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef KEY_PRESS_EVENT_H
#define KEY_PRESS_EVENT_H

#include "AcryEvent.h"
class LifeChangeEvent :
	public AcryEvent
{
private:
	bool m_gain;
	int m_amt;
public:
	LifeChangeEvent(double time, bool gain, int amount);
	virtual ~LifeChangeEvent();

	bool IsGain() const { return m_gain; }
	int Amount() const { return m_amt; }
};

#endif
