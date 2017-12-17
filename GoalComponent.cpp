#include "GoalComponent.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "JsonReader.h"

#include "AcryEvent.h"
#include "GODestroyedEvent.h"
#include "AddScoreEvent.h"
#include <iostream>

void GoalComponent::_SetGoalEnemyCount(unsigned int enemyCount)
{
	m_goalType = GOAL_TYPE::ENEMY_COUNT;
	m_enemyCount = enemyCount;
	m_currentEnemyCount = 0;
}

void GoalComponent::_SetGoalBossDestroyed()
{
	m_goalType = GOAL_TYPE::BOSS_DESTROYED;
	m_bossDestroyed = false;
}

void GoalComponent::_SetDistanceTravelled(double distance)
{
	m_goalType = GOAL_TYPE::DISTANCE_TRAVELLED;
	m_distanceTravelled = distance;
	m_currentDistanceTravelled = 0;
}

void GoalComponent::_GoalCompleted()
{
	if (!m_goalCompleted) {
		GameObject* gObject = GameObjectManager::GetInstance().SpawnGameObject("UI_stage_clear");
		m_goalCompleted = true;
		EventManager::GetInstance().AddDelayedEvent(new AcryEvent(EventType::NEXT_LEVEL, 3.0));
	}
}

GoalComponent::GoalComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::GOAL),
	m_goalCompleted(false)
{}

GoalComponent::GoalComponent(const GoalComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::GOAL),
	m_goalCompleted(rhs.m_goalCompleted)
{}

GoalComponent::~GoalComponent(){}

void GoalComponent::Update(double deltaTime) 
{
	if (m_goalType == GOAL_TYPE::DISTANCE_TRAVELLED) {
		m_currentDistanceTravelled += deltaTime;
		//std::cout << m_currentDistanceTravelled << std::endl;
		if (m_currentDistanceTravelled >= m_distanceTravelled)
			_GoalCompleted();
	}
}

GoalComponent * GoalComponent::Clone(GameObject & parent)
{
	GoalComponent* comp = new GoalComponent(*this, parent);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * GoalComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new GoalComponent(gObject);
}

void GoalComponent::Override(nlohmann::json j)
{
	String type = AcryJson::ParseString(j, "goal", "type");

	if (type == "enemiesDefeated")
		_SetGoalEnemyCount(AcryJson::ParseInt(j, "goal", "count"));
	else if (type == "boss")
		_SetGoalBossDestroyed();
	else if (type == "distance")
		_SetDistanceTravelled(AcryJson::ParseDouble(j, "goal", "distance"));

	_ParseEvents(j, "goal");
	_SubscribeToEvents(this->m_eventsToSubscribeTo);
}

void GoalComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::ADD_SCORE:
	{
		//GODestroyedEvent * godEvent = static_cast<GODestroyedEvent*>(aEvent);
		AddScoreEvent * asEvent = static_cast<AddScoreEvent*>(aEvent);
		if (asEvent->GO()->Tags().HasTag("boss"))
			m_parent.HandleEvent(new AcryEvent(EventType::BOSS_DESTROYED));
		else if (asEvent->GO()->Tags().HasTag("enemy"))
			m_parent.HandleEvent(new AcryEvent(EventType::ENEMY_DESTROYED));
	}
	break;
	case EventType::BOSS_DESTROYED:
	{
		m_bossDestroyed = true;
		_GoalCompleted();
	}
	break;
	case EventType::ENEMY_DESTROYED:
	{
		if (++m_currentEnemyCount >= m_enemyCount)
			_GoalCompleted();
	}
	break;
	case EventType::GAME_OVER:
	{
		GameObject* gObject = GameObjectManager::GetInstance().SpawnGameObject("UI_gameOver");
	}
	break;
	}
}
