#include "UI_MainMenuComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "TextComponent.h"
#include <string>

void UI_MainMenuComponent::_SetText() const
{
	TextComponent * tComp = static_cast<TextComponent*>(m_parent.Get(COMPONENT_TYPE::TEXT));
	tComp->SetText(m_baseMessage);
}

UI_MainMenuComponent::UI_MainMenuComponent(GameObject & parent, String baseMessage) :
	Component(parent, COMPONENT_TYPE::UI_MAIN_MENU),
	m_score(0),
	m_baseMessage(baseMessage) {}

UI_MainMenuComponent::UI_MainMenuComponent(const UI_MainMenuComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_MAIN_MENU),
	m_score(rhs.m_score),
	m_baseMessage(rhs.m_baseMessage) {}

UI_MainMenuComponent::~UI_MainMenuComponent() {}

void UI_MainMenuComponent::Update(double deltaTime) {}

UI_MainMenuComponent * UI_MainMenuComponent::Clone(GameObject & parent)
{
	UI_MainMenuComponent* comp = new UI_MainMenuComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * UI_MainMenuComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_MainMenuComponent* comp = new UI_MainMenuComponent(gObject,
		AcryJson::ParseString(j, "uiScore", "baseMessage")
	);
	comp->_ParseEvents(j, "uiScore");

	return comp;
}

void UI_MainMenuComponent::Override(nlohmann::json j)
{
	m_baseMessage = AcryJson::ValueExists(j, "uiScore", "baseMessage") ? AcryJson::ParseString(j, "uiScore", "baseMessage") : m_baseMessage;
}

void UI_MainMenuComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::ADD_SCORE:
	{
		AddScoreEvent * asEvent = static_cast<AddScoreEvent*>(aEvent);
		AddScore(asEvent->Score());
	}
	break;
	}
}

void UI_MainMenuComponent::LateInitialize()
{
	_SetText();
}

void UI_MainMenuComponent::AddScore(int amt)
{
	m_score += amt;
	_SetText();
}

void UI_MainMenuComponent::RemoveScore(int amt)
{
	m_score -= amt;
	_SetText();
}

void UI_MainMenuComponent::SetScore(int amt)
{
	m_score = amt;
	_SetText();
}
