#include "EventManager.h"
#include "GameObjectManager.h"
#include "SubscriberTracker.h"
#include "Subscriber.h"

#include <utility>
#include <algorithm>

#include <iostream>

EventManager::EventManager() :
	_GameObjectManager(GameObjectManager::GetInstance())
{}

EventManager::~EventManager()
{
	for (AcryEvent* aEvent : m_events) {
		delete aEvent;
	}
	m_events.clear();
}

void EventManager::Update(double deltaTime)
{
	unsigned int i = 0;
	for (i = 0; i < m_events.size(); ++i) {
		m_events[i]->DecrementTime(deltaTime);
		if (m_events[i]->Time() <= 0.0) {
			BroadcastEvent(m_events[i]);
			m_events[i] = nullptr;
		}
	}

	m_events.erase(
		std::remove(m_events.begin(), m_events.end(), nullptr),
		m_events.end()
	);
}

void EventManager::AddDelayedEvent(AcryEvent * newEvent)
{
	m_events.push_back(newEvent);
}

void EventManager::Subscribe(const String eType, Subscriber * subscriber)
{
	m_listeners[AcryEvent::GetEventTypeFromTitle(eType)].push_back(subscriber);
}

void EventManager::Subscribe(const EventType eType, Subscriber * subscriber)
{
	for (Subscriber* listener : m_listeners[eType])
		if (listener = subscriber) return;
	m_listeners[eType].push_back(subscriber);
}


void EventManager::Unsubscribe(Subscriber * subscriber)
{
	for (auto it : m_listeners)
		Unsubscribe(it.first, subscriber);
}

void EventManager::Unsubscribe(const EventType eType, Subscriber * subscriber)
{
	m_listeners[eType].erase(
		std::remove(m_listeners[eType].begin(), m_listeners[eType].end(), subscriber),
		m_listeners[eType].end()
	);
}


void EventManager::UnsubscribeAll(Subscriber * subscriber)
{
	subscriber->UnsubscribeChildrenFromAll();
	Unsubscribe(subscriber);
}


void EventManager::BroadcastEvent(AcryEvent * aEvent)
{
	SubscriberTracker& subscriberTracker = SubscriberTracker::GetInstance();
	unsigned int i = 0;
	for (i = 0; i < subscriberTracker.m_subscribers.size(); ++i) {
		if (subscriberTracker.m_subscribers[i])
			subscriberTracker.m_subscribers[i]->HandleEvent(aEvent);
	}
}

void EventManager::BroadcastEventToSubscribers(AcryEvent * aEvent)
{
	unsigned int i = 0;
	for (i = 0; i < m_listeners[aEvent->Type()].size(); ++i)
		m_listeners[aEvent->Type()][i]->HandleEvent(aEvent);
}
