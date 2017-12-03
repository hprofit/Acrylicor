/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SubscriberTracker.h
Purpose: Tracks all existing Subscriber instances for broadcasting of events
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef SUBSCRIBER_TRACKER_H
#define SUBSCRIBER_TRACKER_H

#include "EventManager.h"
#include <vector>

class Subscriber;

class SubscriberTracker
{
private:
	std::vector<Subscriber*> m_subscribers;

	friend EventManager;

	SubscriberTracker();
	~SubscriberTracker();
public:
	SubscriberTracker(const SubscriberTracker &) = delete;
	void operator=(const SubscriberTracker &) = delete;

	static SubscriberTracker& GetInstance()
	{
		static SubscriberTracker instance;
		return instance;
	}

	void AddSubscriber(Subscriber* subscriber);
	void RemoveSubscriber(Subscriber* subscriber);
};
#endif