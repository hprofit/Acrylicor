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

class AcryEvent
{
protected:
	unsigned int m_time;

	AcryEvent(unsigned int time) : m_time(time) {};
	~AcryEvent();
public:
	AcryEvent() = delete;


	bool operator<(const AcryEvent& rhs);
	bool operator>(const AcryEvent& rhs);
	virtual void Process() = 0;
};

bool operator<(const AcryEvent& lhs, const AcryEvent& rhs);
bool operator>(const AcryEvent& lhs, const AcryEvent& rhs);

struct AcryEventComparator {
	bool operator() (const AcryEvent * left, const AcryEvent * right) const {
		return left->m_time > right->m_time;
	}
};

#endif