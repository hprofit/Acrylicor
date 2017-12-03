/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Subscriber.h
Purpose: Base class for subscribing to events.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "AcrylicorTypedefs.h"
#include "AcryEvent.h"
#include <vector>

class Subscriber
{
protected:
	std::vector<String> m_eventsToSubscribeTo;

	void _SubscribeToEvents(std::vector<String> events);
public:
	Subscriber();
	virtual ~Subscriber();
	virtual void HandleEvent(AcryEvent * aEvent) {};
	virtual void AddEventSubscriptionToSubscribeTo(String eventType);
	virtual void SubscribeToEvent(String eventType);
	virtual void UnsubscribeChildren(String eventType) {};
	virtual void UnsubscribeChildrenFromAll() {};
};

#endif