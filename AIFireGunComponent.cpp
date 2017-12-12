#include "AIFireGunComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "WeaponComponent.h"
#include <iostream>


AIFireGunComponent::AIFireGunComponent(GameObject & parent, float fireFrequency, String gunType) :
	AIBaseComponent(COMPONENT_TYPE::AI_FIRE_GUN, parent),
	m_fireFrequency(fireFrequency),
	m_timeSinceLastFire(0.f),
	m_gunType(gunType)
{}

AIFireGunComponent::AIFireGunComponent(const AIFireGunComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_RUSH, rhs, parent),
	m_fireFrequency(rhs.m_fireFrequency),
	m_timeSinceLastFire(rhs.m_timeSinceLastFire),
	m_gunType(rhs.m_gunType)
{}

AIFireGunComponent::~AIFireGunComponent() {}

void AIFireGunComponent::Update(double deltaTime)
{
	if (m_active) {
		m_timeSinceLastFire += deltaTime;
		if (m_timeSinceLastFire >= m_fireFrequency) {
			m_timeSinceLastFire = 0.f;
			m_wComp->Fire();
		}
	}
}

AIFireGunComponent * AIFireGunComponent::Clone(GameObject & parent)
{
	AIFireGunComponent* comp = new AIFireGunComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AIFireGunComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new AIFireGunComponent(gObject,
		AcryJson::ParseFloat(j, "aiFireGun", "fireFrequency"),
		AcryJson::ParseString(j, "aiFireGun", "gunType")
	);
}

void AIFireGunComponent::Override(nlohmann::json j)
{
	m_fireFrequency = AcryJson::ValueExists(j, "aiFireGun", "fireFrequency") ? AcryJson::ParseInt(j, "aiFireGun", "fireFrequency") : m_fireFrequency;
	m_gunType = AcryJson::ValueExists(j, "aiFireGun", "gunType") ? AcryJson::ParseString(j, "aiFireGun", "gunType") : m_gunType;
}

void AIFireGunComponent::LateInitialize()
{
	m_wComp = static_cast<WeaponComponent*>(m_parent.GetChildOfType(m_gunType)->Get(COMPONENT_TYPE::WEAPON));
	if (!m_wComp)
		std::cout << "AIFireGun components require Weapon components." << std::endl;
}
