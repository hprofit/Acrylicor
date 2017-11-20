#include "UI_MissilesComponent.h"
#include "JsonReader.h"

#include "GameObject.h"

UI_MissilesComponent::UI_MissilesComponent(GameObject & parent, String baseMessage) :
	Component(parent, COMPONENT_TYPE::UI_MISSILES),
	m_count(0),
	m_baseMessage(baseMessage) {}

UI_MissilesComponent::UI_MissilesComponent(const UI_MissilesComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_MISSILES),
	m_count(rhs.m_count),
	m_baseMessage(rhs.m_baseMessage) {} {}

UI_MissilesComponent::~UI_MissilesComponent()
{
}

void UI_MissilesComponent::Update(double deltaTime)
{
}

UI_MissilesComponent * UI_MissilesComponent::Clone(GameObject & parent)
{
	UI_MissilesComponent* comp = new UI_MissilesComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * UI_MissilesComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_MissilesComponent* uilComp = new UI_MissilesComponent(gObject,
		AcryJson::ParseString(j, "uiMissiles", "baseMessage")
	);
	if (AcryJson::ValueExists(j, "uiMissiles", "events")) {
		int numObjs = j["uiMissiles"]["events"].size();
		for (int i = 0; i < numObjs; ++i) {
			uilComp->AddEventSubscription(j["uiMissiles"]["events"][i]);
		}
	}

	return uilComp;
}

void UI_MissilesComponent::Override(nlohmann::json j)
{
	m_baseMessage = AcryJson::ValueExists(j, "uiMissiles", "baseMessage") ? AcryJson::ParseString(j, "uiMissiles", "baseMessage") : m_baseMessage;
}

void UI_MissilesComponent::HandleEvent(AcryEvent * aEvent)
{
}

void UI_MissilesComponent::AddMissile()
{

}

void UI_MissilesComponent::AddMissiles(int amt)
{
}

void UI_MissilesComponent::RemoveMissile()
{
}

void UI_MissilesComponent::RemoveMissiles(int amt)
{
}
