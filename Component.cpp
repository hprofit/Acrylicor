#include "Component.h"
#include "EventManager.h"
#include "JsonReader.h"

void Component::AddEventSubscription(String eventType)
{
	m_eventsToSubscribeTo.push_back(eventType);
}

void Component::_SubscribeToEvents(std::vector<String> events)
{
	for (String eventType : events)
		EventManager::GetInstance().Subscribe(eventType, this);
}

void Component::_ParseEvents(nlohmann::json j, String componentString)
{
	if (AcryJson::ValueExists(j, componentString, "events")) {
		int numObjs = j[componentString]["events"].size();
		for (int i = 0; i < numObjs; ++i) {
			AddEventSubscription(j[componentString]["events"][i]);
		}
	}
}
