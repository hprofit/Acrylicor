#include "EventManager.h"



EventManager::EventManager()
{
}


EventManager::~EventManager()
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
		m_time = nextEvent->m_time;
		nextEvent->Process();
		delete nextEvent;
	}
}
