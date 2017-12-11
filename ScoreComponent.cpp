#include "ScoreComponent.h"
#include "JsonReader.h"

#include "AcryEvent.h"
#include "AddScoreEvent.h"
#include "EventManager.h"
#include <iostream>

ScoreComponent::ScoreComponent(GameObject& parent, int scoreValue) :
	Component(parent, COMPONENT_TYPE::SCORE),
	m_scoreValue(scoreValue)
{
}

ScoreComponent::ScoreComponent(const ScoreComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::SCORE),
	m_scoreValue(rhs.m_scoreValue)
{}

ScoreComponent::~ScoreComponent(){}

void ScoreComponent::Update(double deltaTime){}

ScoreComponent * ScoreComponent::Clone(GameObject & parent)
{
	ScoreComponent* comp = new ScoreComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * ScoreComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new ScoreComponent(gObject, AcryJson::ParseInt(j, "score", "amount"));
}

void ScoreComponent::Override(nlohmann::json j)
{
	m_scoreValue = AcryJson::ValueExists(j, "score", "amount") ? AcryJson::ParseInt(j, "score", "amount") : m_scoreValue;
}

void ScoreComponent::HandleEvent(AcryEvent * aEvent)
{
	//switch (aEvent->Type()) {
	//case EventType::SCORE:
	//{
	//	EventManager::GetInstance().BroadcastEventToSubscribers(new AddScoreEvent(m_scoreValue, &m_parent));
	//}
	//break;
	//}
}
