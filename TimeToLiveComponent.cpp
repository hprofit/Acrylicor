#include "TimeToLiveComponent.h"
#include "JsonReader.h"
#include "GameObjectManager.h"
#include <iostream>

TimeToLiveComponent::TimeToLiveComponent(GameObject& parent, double timeToLive) :
	Component(parent, COMPONENT_TYPE::TIME_TO_LIVE),
	m_timeToLive(timeToLive), m_timePassed(0.f)
{}

TimeToLiveComponent::TimeToLiveComponent(const TimeToLiveComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::TIME_TO_LIVE),
	m_timeToLive(rhs.m_timeToLive), m_timePassed(rhs.m_timePassed)
{}

TimeToLiveComponent::~TimeToLiveComponent(){}

void TimeToLiveComponent::Update(double deltaTime)
{
	m_timePassed += deltaTime;

	if (m_timePassed >= m_timeToLive) {
		GameObjectManager::GetInstance().DestroyGameObject(&m_parent);
	}
}

TimeToLiveComponent * TimeToLiveComponent::Clone(GameObject & parent)
{
	TimeToLiveComponent* comp = new TimeToLiveComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * TimeToLiveComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new TimeToLiveComponent(gObject, AcryJson::ParseDouble(j, "ttl", "time"));
}

void TimeToLiveComponent::Override(nlohmann::json j)
{
	m_timeToLive = AcryJson::ValueExists(j, "ttl", "time") ? AcryJson::ParseDouble(j, "ttl", "time") : m_timeToLive;
}

void TimeToLiveComponent::HandleEvent(AcryEvent * aEvent){}