#include "GoalComponent.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "JsonReader.h"

#include "AcryEvent.h"
#include "GODestroyedEvent.h"

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

void GoalComponent::_SetDistanceTravelled(float distance)
{
	m_goalType = GOAL_TYPE::DISTANCE_TRAVELLED;
	m_distanceTravelled = distance;
	m_currentDistanceTravelled = 0;
}

GoalComponent::GoalComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::GOAL)
{}

GoalComponent::GoalComponent(const GoalComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::GOAL)
{}

GoalComponent::~GoalComponent(){}

void GoalComponent::Update(double deltaTime)
{
}

GoalComponent * GoalComponent::Clone(GameObject & parent)
{
	GoalComponent* comp = new GoalComponent(*this, parent);
	//comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
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
		_SetDistanceTravelled(AcryJson::ParseFloat(j, "goal", "distance"));

	_ParseEvents(j, "goal");
	_SubscribeToEvents(this->m_eventsToSubscribeTo);
}

void GoalComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::GO_DESTROYED:
	{
		GODestroyedEvent * godEvent = static_cast<GODestroyedEvent*>(aEvent);
		if (godEvent->GO()->Tags().HasTag("boss"))
			m_parent.HandleEvent(new AcryEvent(EventType::BOSS_DESTROYED, 0.0));
		else if (godEvent->GO()->Tags().HasTag("enemy"))
			m_parent.HandleEvent(new AcryEvent(EventType::ENEMY_DESTROYED, 0.0));

	}
	break;
	case EventType::BOSS_DESTROYED:
	{
		m_bossDestroyed = true;
		std::cout << "Boss Destroyed: Goal reached!" << std::endl;
	}
	break;
	case EventType::ENEMY_DESTROYED:
	{
		if (++m_currentEnemyCount >= m_enemyCount)
			std::cout << "======================== Enemies destroyed: Goal reached! ========================" << std::endl;
	}
	break;
	}
}
