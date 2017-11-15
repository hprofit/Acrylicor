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

#include <map>
#include <queue>
#include <functional>
#include "AcryEvent.h"
#include "AcrylicorTypedefs.h"

class GameObjectManager;
class GameObject;

class EventManager
{
private:
	std::map<EventType, std::vector<GameObject*> > m_listeners;
	std::priority_queue<AcryEvent*, std::vector<AcryEvent*>, AcryEventComparator> m_eventQueue;
	unsigned int m_time;
	GameObjectManager& _GameObjectManager;

	EventManager();
	~EventManager();
public:
	EventManager(const EventManager &) = delete;
	void operator=(const EventManager &) = delete;

	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	void Update();
	void AddEvent(AcryEvent * newEvent);
	void RunEvent();
	void Subscribe(EventType eType, GameObject* gObject);

	void BroadcastEvent(AcryEvent * aEvent);
	void BroadcastEventToSubscribers(AcryEvent * aEvent);
};

#endif