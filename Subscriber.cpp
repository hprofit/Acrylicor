#include "Subscriber.h"
#include "EventManager.h"
#include "SubscriberTracker.h"

Subscriber::Subscriber()
{
	SubscriberTracker::GetInstance().AddSubscriber(this);
}

Subscriber::~Subscriber()
{
	SubscriberTracker::GetInstance().RemoveSubscriber(this);
}

void Subscriber::_SubscribeToEvents(std::vector<String> events)
{
	for (String eventType : events)
		EventManager::GetInstance().Subscribe(eventType, this);
}

void Subscriber::AddEventSubscriptionToSubscribeTo(String eventType)
{
	m_eventsToSubscribeTo.push_back(eventType);
}

void Subscriber::SubscribeToEvent(String eventType)
{
	EventManager::GetInstance().Subscribe(eventType, this);
}
