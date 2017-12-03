/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LoadLevelEvent.h
Purpose: Event that specifies which level to be loaded.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef LOAD_LEVEL_EVENT_H
#define LOAD_LEVEL_EVENT_H

#include "AcryEvent.h"

class LoadLevelEvent :
	public AcryEvent
{
public:
	const unsigned int level;

	LoadLevelEvent(double time, unsigned int _level);
	virtual ~LoadLevelEvent();

};
#endif
