/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Event.h
Purpose: Event base class for use by various game objects and the EventManager.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <queue>
#include "AcrylicorTypedefs.h"

enum class EventType {
	COLLIDE,
	KEY_PRESS
};

struct AcryEventComparator;

class AcryEvent
{
protected:
	double m_time;
	EventType m_type;
	// Payload
	// Message specific data

	AcryEvent(double time) : m_time(time) {};
public:
	AcryEvent(EventType type, unsigned int time);
	AcryEvent() = delete;
	virtual ~AcryEvent();

	friend AcryEventComparator;
	friend bool operator<(const AcryEvent& lhs, const AcryEvent& rhs);
	friend bool operator>(const AcryEvent& lhs, const AcryEvent& rhs);

	bool operator<(const AcryEvent& rhs);
	bool operator>(const AcryEvent& rhs);
	unsigned int Time() const {
		return m_time;
	}
	EventType Type() const {
		return m_type;
	}
	void DecrementTime(double amt) {
		m_time -= amt;
	}
};

bool operator<(const AcryEvent& lhs, const AcryEvent& rhs);
bool operator>(const AcryEvent& lhs, const AcryEvent& rhs);

struct AcryEventComparator {
	bool operator() (const AcryEvent * left, const AcryEvent * right) const {
		return left->m_time > right->m_time;
	}
};

#endif