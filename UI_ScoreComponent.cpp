#include "UI_ScoreComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "MissileCountChangeEvent.h"
#include "TextComponent.h"
#include <string>

void UI_ScoreComponent::_SetText() const
{
	TextComponent * tComp = static_cast<TextComponent*>(m_parent.Get(COMPONENT_TYPE::TEXT));
	tComp->SetText(m_baseMessage + std::to_string(m_score));
}

UI_ScoreComponent::UI_ScoreComponent(GameObject & parent, String baseMessage) :
	Component(parent, COMPONENT_TYPE::UI_SCORE),
	m_score(0),
	m_baseMessage(baseMessage) {}

UI_ScoreComponent::UI_ScoreComponent(const UI_ScoreComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_SCORE),
	m_score(rhs.m_score),
	m_baseMessage(rhs.m_baseMessage) {}

UI_ScoreComponent::~UI_ScoreComponent()
{
}

void UI_ScoreComponent::Update(double deltaTime)
{
}

UI_ScoreComponent * UI_ScoreComponent::Clone(GameObject & parent)
{
	UI_ScoreComponent* comp = new UI_ScoreComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * UI_ScoreComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_ScoreComponent* uilComp = new UI_ScoreComponent(gObject,
		AcryJson::ParseString(j, "uiScore", "baseMessage")
	);
	uilComp->_ParseEvents(j, "uiScore");

	return uilComp;
}

void UI_ScoreComponent::Override(nlohmann::json j)
{
	m_baseMessage = AcryJson::ValueExists(j, "uiScore", "baseMessage") ? AcryJson::ParseString(j, "uiScore", "baseMessage") : m_baseMessage;
}

void UI_ScoreComponent::HandleEvent(AcryEvent * aEvent)
{

}

void UI_ScoreComponent::LateInitialize()
{
	_SetText();
}

void UI_ScoreComponent::AddScore(int amt)
{
	m_score += amt;
	_SetText();
}

void UI_ScoreComponent::RemoveScore(int amt)
{
	m_score -= amt;
	_SetText();
}

void UI_ScoreComponent::SetScore(int amt)
{
	m_score = amt;
	_SetText();
}
