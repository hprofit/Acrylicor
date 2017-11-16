#include "DamageComponent.h"
#include "JsonReader.h"
#include "DamageEvent.h"
#include "GameObject.h"

DamageComponent::DamageComponent(GameObject & parent, int damage) :
	Component(parent, COMPONENT_TYPE::DAMAGE),
	m_damage(damage) {}

DamageComponent::DamageComponent(const DamageComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::DAMAGE),
	m_damage(rhs.m_damage) {}

DamageComponent::~DamageComponent()
{
}

void DamageComponent::Update(double deltaTime)
{
}

DamageComponent * DamageComponent::Clone(GameObject & parent)
{
	return new DamageComponent(*this, parent);
}

Component * DamageComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	int damage = AcryJson::ParseInt(j, "damage", "amount");
	return new DamageComponent(gObject, damage);
}

void DamageComponent::Override(nlohmann::json j)
{
	m_damage = AcryJson::ValueExists(j, "damage", "amount") ? AcryJson::ParseInt(j, "damage", "amount") : m_damage;
}

void DamageComponent::HandleEvent(AcryEvent * aEvent)
{
}
