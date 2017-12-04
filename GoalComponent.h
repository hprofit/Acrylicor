/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GoalComponent.h
Purpose: Keeps track of the goal for the current level, be it number of enemies cleared, specific types, or length travelled
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GOAL_COMPONENT_H
#define GOAL_COMPONENT_H

#include "Component.h"
#include "AcrylicorTypedefs.h"

const enum class GOAL_TYPE {
	ENEMY_COUNT = 0,
	BOSS_DESTROYED,
	DISTANCE_TRAVELLED
};

class GoalComponent :
	public Component
{
protected:
	GOAL_TYPE m_goalType;

	bool m_goalCompleted;

	unsigned int m_enemyCount;
	unsigned int m_currentEnemyCount;

	bool m_bossDestroyed;

	float m_distanceTravelled;
	float m_currentDistanceTravelled;

	void _SetGoalEnemyCount(unsigned int enemyCount);
	void _SetGoalBossDestroyed();
	void _SetDistanceTravelled(float distance);

	void _GoalCompleted();
public:
	GoalComponent() = delete;
	GoalComponent(GameObject& parent);
	GoalComponent(const GoalComponent& rhs, GameObject& parent);
	virtual ~GoalComponent();

	virtual void Update(double deltaTime);
	virtual GoalComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
};

#endif
