#include "WeaponComponent.h"
#include "JsonReader.h"
#include "GameObjectManager.h"

// Don't like TODO: fix
#include "GameObject.h"
#include "TransformComponent.h"

WeaponComponent::WeaponComponent(GameObject & parent, float rateOfFire, String bulletType, unsigned int burstAmount) :
	Component(parent, CT_WEAPON),
	m_rateOfFire(rateOfFire),
	m_bulletType(bulletType),
	m_burstAmount(burstAmount),
	m_timeSinceLastFired(0.f)
{}

WeaponComponent::WeaponComponent(const WeaponComponent & rhs, GameObject & parent) :
	Component(parent, CT_WEAPON),
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
	return new WeaponComponent(*this, parent);
}

Component * WeaponComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new WeaponComponent(gObject,
		AcryJson::ParseFloat(j, "weapon", "rateOfFire"),
		AcryJson::ParseString(j, "weapon", "bullet"),
		AcryJson::ValueExists(j, "weapon", "burst") ? AcryJson::ParseInt(j, "weapon", "burst") : 1
	);
}

void WeaponComponent::Override(nlohmann::json j)
{
	m_rateOfFire = AcryJson::ValueExists(j, "weapon", "rateOfFire") ? AcryJson::ParseFloat(j, "weapon", "rateOfFire") : m_rateOfFire;
	m_bulletType = AcryJson::ValueExists(j, "weapon", "bullet") ? AcryJson::ParseString(j, "weapon", "bullet") : m_bulletType;
	m_burstAmount = AcryJson::ValueExists(j, "weapon", "burst") ? AcryJson::ParseInt(j, "weapon", "burst") : m_burstAmount;
}

void WeaponComponent::Fire()
{
	if (m_timeSinceLastFired >= m_rateOfFire) {
		m_timeSinceLastFired = 0.f;
		GameObject * bullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);
		TransformComponent * bulletTComp = static_cast<TransformComponent*>(bullet->Get(CT_TRANSFORM));
		TransformComponent * playerTComp = static_cast<TransformComponent*>(m_parent.Get(CT_TRANSFORM));
		if (!bulletTComp || !playerTComp)
			return;
		bulletTComp->SetPosition(playerTComp->GetPosition());
		bulletTComp->SetAngles(playerTComp->GetAngleX(), playerTComp->GetAngleY(), playerTComp->GetAngleZ());
	}
}
