#include "EventManager.h"
#include "GameObjectManager.h"


EventManager::EventManager() :
	_GameObjectManager(GameObjectManager::GetInstance())
{}


EventManager::~EventManager()
{
	while (!m_eventQueue.empty()) {
		AcryEvent * nextEvent = m_eventQueue.top();
		m_eventQueue.pop();
		delete nextEvent;
	}
	m_eventQueue.empty();
}

void EventManager::Update()
{

}

void EventManager::AddEvent(AcryEvent * newEvent)
{
	m_eventQueue.push(newEvent);
}

void EventManager::RunEvent()
{
	while (!m_eventQueue.empty()) {
		AcryEvent * nextEvent = m_eventQueue.top();
		m_eventQueue.pop();
		m_time = nextEvent->Time();
		//nextEvent->Process(m_listeners[nextEvent->Type()] );
		delete nextEvent;
	}
}

void EventManager::Subscribe(EventType eType, GameObject * gObject)
{
	unsigned int i = 0;
	for (i = 0; i < m_listeners[eType].size(); ++i) {
		if (m_listeners[eType][i] == gObject)
			return;
	}
	m_listeners[eType].push_back(gObject);
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
	for (i = 0; i < m_listeners[aEvent->Type()].size(); ++i) {
		m_listeners[aEvent->Type()][i]->HandleEvent(aEvent);
	}
}
