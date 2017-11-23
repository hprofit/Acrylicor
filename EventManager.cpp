#include "EventManager.h"
#include "GameObjectManager.h"

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


void EventManager::Subscribe(const String eType, GameObject * gObject)
{
	EventType t = AcryEvent::GetEventTypeFromTitle("junk");
	m_listeners[AcryEvent::GetEventTypeFromTitle(eType)].first.push_back(gObject);
}

void EventManager::Subscribe(const EventType eType, GameObject * gObject)
{
	for (GameObject* listener : m_listeners[eType].first)
		if (listener = gObject) return;
	m_listeners[eType].first.push_back(gObject);
}

void EventManager::Subscribe(const String eType, Component * component)
{
	m_listeners[AcryEvent::GetEventTypeFromTitle(eType)].second.push_back(component);
}

void EventManager::Subscribe(const EventType eType, Component * component)
{
	for (Component* listener : m_listeners[eType].second)
		if (listener = component) return;
	m_listeners[eType].second.push_back(component);
}


void EventManager::Unsubscribe(GameObject * gObject)
{
	for (auto it : m_listeners)
		Unsubscribe(it.first, gObject);
}

void EventManager::Unsubscribe(const EventType eType, GameObject * gObject)
{
	m_listeners[eType].first.erase(
		std::remove(m_listeners[eType].first.begin(), m_listeners[eType].first.end(), gObject),
		m_listeners[eType].first.end()
	);
}

void EventManager::Unsubscribe(Component * component)
{
	for (auto it : m_listeners)
		Unsubscribe(it.first, component);
}

void EventManager::Unsubscribe(const EventType eType, Component * component)
{
	m_listeners[eType].second.erase(
		std::remove(m_listeners[eType].second.begin(), m_listeners[eType].second.end(), component),
		m_listeners[eType].second.end()
	);
}

void EventManager::UnsubscribeAll(GameObject * gObject)
{
	std::map<COMPONENT_TYPE, Component*> components = gObject->GetComponents();
	std::map<COMPONENT_TYPE, Component*>::iterator it;

	for (it = components.begin(); it != components.end(); ++it) {
		Unsubscribe(it->second);
	}
	Unsubscribe(gObject);
}


void EventManager::BroadcastEvent(AcryEvent * aEvent)
{
	unsigned int i = 0;
	for (i = 0; i < _GameObjectManager.m_gameObjects.size(); ++i) {
		if (_GameObjectManager.m_gameObjects[i] && _GameObjectManager.m_gameObjects[i]->IsActive())
			_GameObjectManager.m_gameObjects[i]->HandleEvent(aEvent);
	}
}

void EventManager::BroadcastEventToSubscribers(AcryEvent * aEvent)
{
	unsigned int i = 0;
	for (i = 0; i < m_listeners[aEvent->Type()].first.size(); ++i)
		m_listeners[aEvent->Type()].first[i]->HandleEvent(aEvent);

	for (i = 0; i < m_listeners[aEvent->Type()].second.size(); ++i)
		m_listeners[aEvent->Type()].second[i]->HandleEvent(aEvent);
}
