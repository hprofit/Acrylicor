#include "Component.h"
#include "EventManager.h"
#include "JsonReader.h"

void Component::_ParseEvents(nlohmann::json j, String componentString)
{
	if (AcryJson::ValueExists(j, componentString, "events")) {
		int numObjs = j[componentString]["events"].size();
		for (int i = 0; i < numObjs; ++i) {
			AddEventSubscriptionToSubscribeTo(j[componentString]["events"][i]);
		}
	}
}

