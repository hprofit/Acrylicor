#include "Component.h"
#include "EventManager.h"

void Component::AddEventSubscription(String eventType)
{
	m_eventsToSubscribeTo.push_back(eventType);
}

void Component::_SubscribeToEvents(std::vector<String> events)
{
	for (String eventType : events)
		EventManager::GetInstance().Subscribe(eventType, this);
}
