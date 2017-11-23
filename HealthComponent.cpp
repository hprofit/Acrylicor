#include "HealthComponent.h"
#include "JsonReader.h"
#include "DamageEvent.h"
#include "GameObject.h"
#include "GameObjectManager.h"

HealthComponent::HealthComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::HEALTH),
	m_hitPoints(0) {}

HealthComponent::HealthComponent(GameObject & parent, int hitPoints) :
	Component(parent, COMPONENT_TYPE::HEALTH),
	m_hitPoints(hitPoints) {}

HealthComponent::HealthComponent(const HealthComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::HEALTH),
	m_hitPoints(rhs.m_hitPoints) {}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update(double deltaTime)
{
}

HealthComponent * HealthComponent::Clone(GameObject & parent)
{
	HealthComponent* comp = new HealthComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * HealthComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	int hitPoints = AcryJson::ParseInt(j, "health", "hp");
	return new HealthComponent(gObject, hitPoints);
}

void HealthComponent::Override(nlohmann::json j)
{
	m_hitPoints = AcryJson::ValueExists(j, "health", "hp") ? AcryJson::ParseInt(j, "health", "hp") : m_hitPoints;
}

void HealthComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::DAMAGE:
	{
		DamageEvent * dpEvent = static_cast<DamageEvent*>(aEvent);
		m_hitPoints -= dpEvent->Amount();

		// TODO: Event that plays death animation
		if (m_hitPoints <= 0)
			GameObjectManager::GetInstance().DestroyGameObject(&m_parent);
	}
	break;
	}
}
