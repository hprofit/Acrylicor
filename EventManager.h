/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManager.h
Purpose: Contains and manages the Event queue.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <queue>
#include <functional>
#include "AcryEvent.h"

class EventManager
{
private:
	std::priority_queue<AcryEvent*, std::vector<AcryEvent*>, AcryEventComparator> m_eventQueue;
	unsigned int m_time;

	EventManager();
	~EventManager();
public:
	EventManager(EventManager const&) = delete;
	void operator=(EventManager const&) = delete;

	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	void AddEvent(AcryEvent * newEvent);
	void RunEvent();
};

#endif