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

#include <unordered_map>
#include <utility>
#include "AcrylicorTypedefs.h"
#include "AcryEvent.h"

class GameObjectManager;
class GameObject;
class Component;

class EventManager
{
private:
	std::unordered_map<EventType, std::pair<std::vector<GameObject*>, std::vector<Component*> > > m_listeners;
	std::vector<AcryEvent*> m_events;
	double m_time;
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

	void Update(double deltaTime);
	void AddDelayedEvent(AcryEvent * newEvent);

	void Subscribe(const String eType, GameObject* gObject);
	void Subscribe(EventType eType, GameObject* gObject);

	void Subscribe(const String eType, Component* component);
	void Subscribe(const EventType eType, Component* component);

	void Unsubscribe(GameObject* gObject);
	void Unsubscribe(const EventType eType, GameObject* gObject);

	void Unsubscribe(Component* component);
	void Unsubscribe(const EventType eType, Component* component);

	void BroadcastEvent(AcryEvent * aEvent);
	void BroadcastEventToSubscribers(AcryEvent * aEvent);
};

#endif