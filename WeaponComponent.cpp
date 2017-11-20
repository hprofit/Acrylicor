#include "WeaponComponent.h"
#include "JsonReader.h"
#include "GameObjectManager.h"

// Don't like TODO: fix
#include "GameObject.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"

WeaponComponent::WeaponComponent(GameObject & parent, double rateOfFire, String bulletType, unsigned int burstAmount) :
	Component(parent, COMPONENT_TYPE::WEAPON),
	m_rateOfFire(rateOfFire),
	m_bulletType(bulletType),
	m_burstAmount(burstAmount),
	m_timeSinceLastFired(0.0)
{}

WeaponComponent::WeaponComponent(const WeaponComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::WEAPON),
	m_rateOfFire(rhs.m_rateOfFire),
	m_bulletType(rhs.m_bulletType),
	m_burstAmount(rhs.m_burstAmount),
	m_timeSinceLastFired(rhs.m_timeSinceLastFired)
{}

WeaponComponent::~WeaponComponent()
{
}

void WeaponComponent::Update(double deltaTime)
{
	if (m_timeSinceLastFired < m_rateOfFire)
		m_timeSinceLastFired += deltaTime;
}

WeaponComponent * WeaponComponent::Clone(GameObject & parent)
{
	WeaponComponent* comp = new WeaponComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * WeaponComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new WeaponComponent(gObject,
		AcryJson::ParseDouble(j, "weapon", "rateOfFire"),
		AcryJson::ParseString(j, "weapon", "bullet"),
		AcryJson::ValueExists(j, "weapon", "burst") ? AcryJson::ParseInt(j, "weapon", "burst") : 1
	);
}

void WeaponComponent::Override(nlohmann::json j)
{
	m_rateOfFire = AcryJson::ValueExists(j, "weapon", "rateOfFire") ? AcryJson::ParseDouble(j, "weapon", "rateOfFire") : m_rateOfFire;
	m_bulletType = AcryJson::ValueExists(j, "weapon", "bullet") ? AcryJson::ParseString(j, "weapon", "bullet") : m_bulletType;
	m_burstAmount = AcryJson::ValueExists(j, "weapon", "burst") ? AcryJson::ParseInt(j, "weapon", "burst") : m_burstAmount;
}

void WeaponComponent::Fire()
{
	if (m_timeSinceLastFired >= m_rateOfFire) {
		m_timeSinceLastFired = 0.f;
		GameObject * bullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);

		TransformComponent * bulletTComp = static_cast<TransformComponent*>(bullet->Get(COMPONENT_TYPE::TRANSFORM));
		PhysicsComponent * bulletPComp = static_cast<PhysicsComponent*>(bullet->Get(COMPONENT_TYPE::PHYSICS));

		TransformComponent * gunTComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
		PhysicsComponent * gunPComp = static_cast<PhysicsComponent*>(m_parent.GetImmediate(COMPONENT_TYPE::PHYSICS));

		if (!bulletTComp || !bulletPComp || !gunTComp)
			return;

		bulletTComp->SetPosition(gunTComp->GetPosition());
		bulletTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ());

		if (gunPComp) {
			bulletPComp->SetPosition(gunPComp->GetPosition());
			bulletPComp->SetPrevPosition(gunPComp->GetPrevPosition());
		}
		else {
			bulletPComp->SetPosition(gunTComp->GetPosition());
			bulletPComp->SetPrevPosition(gunTComp->GetPosition());
		}
	}
}
