#include "UI_LivesComponent.h"
#include "JsonReader.h"
#include "LifeChangeEvent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

UI_LivesComponent::UI_LivesComponent(GameObject & parent, float scaleX, float scaleY, int lives) :
	Component(parent, COMPONENT_TYPE::UI_LIVES),
	m_lives(lives),
	m_scaleX(scaleX),
	m_scaleY(scaleY)
{}

UI_LivesComponent::UI_LivesComponent(const UI_LivesComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_LIVES),
	m_lives(rhs.m_lives),
	m_scaleX(rhs.m_scaleX),
	m_scaleY(rhs.m_scaleY)
{}

UI_LivesComponent::~UI_LivesComponent() {}

void UI_LivesComponent::Update(double deltaTime)
{
	SpriteComponent* sComp = static_cast<SpriteComponent*>(m_parent.Get(COMPONENT_TYPE::SPRITE));
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));

	tComp->SetScaleX(m_scaleX * m_lives);
	tComp->SetScaleY(m_scaleY);
	sComp->SetTileX((float)m_lives);
}

UI_LivesComponent * UI_LivesComponent::Clone(GameObject & parent)
{
	UI_LivesComponent * comp = new UI_LivesComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * UI_LivesComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_LivesComponent* comp = new UI_LivesComponent(gObject,
		AcryJson::ParseFloat(j, "uiLives", "scale", "x"),
		AcryJson::ParseFloat(j, "uiLives", "scale", "y"),
		AcryJson::ParseInt(j, "uiLives", "amount")
	);
	comp->_ParseEvents(j, "uiLives");
	return comp;
}

void UI_LivesComponent::Override(nlohmann::json j)
{
	m_scaleX = AcryJson::ValueExists(j, "uiLives", "scale", "x") ? AcryJson::ParseFloat(j, "uiLives", "scale", "x") : m_scaleX;
	m_scaleY = AcryJson::ValueExists(j, "uiLives", "scale", "y") ? AcryJson::ParseFloat(j, "uiLives", "scale", "y") : m_scaleY;
	m_lives = AcryJson::ValueExists(j, "uiLives", "amount") ? AcryJson::ParseInt(j, "uiLives", "amount") : m_lives;
}

void UI_LivesComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::LIFE_CHANGE:
	{
		LifeChangeEvent * lcpEvent = static_cast<LifeChangeEvent*>(aEvent);

		if (lcpEvent->IsGain())
			AddLives(lcpEvent->Amount());
		else
			RemoveLives(lcpEvent->Amount());
	}
	break;
	case EventType::PLAYER_DEATH:
	{
		RemoveLife();
	}
	break;
	}
}

void UI_LivesComponent::AddLife()
{
	++m_lives;
}

void UI_LivesComponent::AddLives(int amt)
{
	m_lives += amt;
}

void UI_LivesComponent::RemoveLife()
{
	--m_lives;
}

void UI_LivesComponent::RemoveLives(int amt)
{ 
	m_lives -= amt;
}
