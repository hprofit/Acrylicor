#include "UI_MissilesComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "MissileCountChangeEvent.h"
#include "MissileAddedEvent.h"
#include "TextComponent.h"
#include <string>

void UI_MissilesComponent::_SetText() const
{
	TextComponent * tComp = static_cast<TextComponent*>(m_parent.Get(COMPONENT_TYPE::TEXT));
	tComp->SetText(m_baseMessage + std::to_string(m_count));
}

UI_MissilesComponent::UI_MissilesComponent(GameObject & parent, String baseMessage) :
	Component(parent, COMPONENT_TYPE::UI_MISSILES),
	m_count(0),
	m_baseMessage(baseMessage) {}

UI_MissilesComponent::UI_MissilesComponent(const UI_MissilesComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_MISSILES),
	m_count(rhs.m_count),
	m_baseMessage(rhs.m_baseMessage) {}

UI_MissilesComponent::~UI_MissilesComponent(){}

void UI_MissilesComponent::Update(double deltaTime)
{
}

UI_MissilesComponent * UI_MissilesComponent::Clone(GameObject & parent)
{
	UI_MissilesComponent* comp = new UI_MissilesComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * UI_MissilesComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_MissilesComponent* comp = new UI_MissilesComponent(gObject,
		AcryJson::ParseString(j, "uiMissiles", "baseMessage")
	);
	comp->_ParseEvents(j, "uiMissiles");

	return comp;
}

void UI_MissilesComponent::Override(nlohmann::json j)
{
	m_baseMessage = AcryJson::ValueExists(j, "uiMissiles", "baseMessage") ? AcryJson::ParseString(j, "uiMissiles", "baseMessage") : m_baseMessage;
}

void UI_MissilesComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::MISSILE_ADDED:
	{
		MissileAddedEvent* maEvent = static_cast<MissileAddedEvent*>(aEvent);
		AddMissiles(maEvent->Amount());
	}
	break;

	case EventType::MISSILE_FIRED:
	{
		RemoveMissile();
	}
	break;

	case EventType::MISSILE_COUNT_CHANGE:
	{
		MissileCountChangeEvent* mccEvent = static_cast<MissileCountChangeEvent*>(aEvent);
		SetMissileCount(mccEvent->Count());
	}
	break;
	}
}

void UI_MissilesComponent::AddMissile()
{
	++m_count;
	_SetText();
}

void UI_MissilesComponent::AddMissiles(int amt)
{
	m_count += amt;
	_SetText();
}

void UI_MissilesComponent::RemoveMissile()
{
	--m_count;
	_SetText();
}

void UI_MissilesComponent::RemoveMissiles(int amt)
{
	m_count -= amt;
	_SetText();
}

void UI_MissilesComponent::SetMissileCount(int amt)
{
	m_count = amt;
	_SetText();
}
