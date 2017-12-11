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

#include "AcrylicorTypedefs.h"

enum class EventType {
	NEXT_LEVEL,
	RESTART_LEVEL,
	LOAD_LEVEL,
	UNLOAD_LEVEL,
	GAME_OVER,

	DATA_AMOUNT,
	GO_DESTROYED,
	ENEMY_DESTROYED,
	BOSS_DESTROYED,

	COLLIDE,
	COLLIDE_KILL_ZONE,
	REFLECT,
	PUSH_FROM_BODY,

	KEY_PRESS,
	KEY_RELEASED,
	KEY_TRIGGERED,
	MOUSE_MOTION,

	DAMAGE,
	USE_ENERGY,
	LIFE_CHANGE,
	PLAYER_DEATH,
	RESPAWN,
	SPAWN,
	MISSILE_FIRED,
	MISSILE_ADDED,
	MISSILE_COUNT_CHANGE,
	DASH,
	TARGET_FOUND,
	PICKUP,
	SHAKE,
	SCORE,
	ADD_SCORE
};

class AcryEvent
{
protected:
	double m_time;
	EventType m_type;
	// Payload
	// Message specific data
public:
	AcryEvent(EventType type, double time = 0.0);
	virtual ~AcryEvent();

	double Time() const;
	EventType Type() const;
	void DecrementTime(double amt);

	static EventType GetEventTypeFromTitle(String eventTitle);
};

#endif