#include "WeaponComponent.h"
#include "JsonReader.h"
#include "GameObjectManager.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "PickupEvent.h"

void WeaponComponent::_FireSingleBarrel()
{
	GameObject * bullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);

	TransformComponent * bulletTComp = static_cast<TransformComponent*>(bullet->Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent * bulletPComp = static_cast<PhysicsComponent*>(bullet->Get(COMPONENT_TYPE::PHYSICS));

	TransformComponent * gunTComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));

	if (!bulletTComp || !bulletPComp || !gunTComp)
		return;

	Vector3D pos = gunTComp->GetPosition();

	bulletTComp->SetPosition(pos);
	bulletTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ());

	bulletPComp->SetPosition(pos);
	bulletPComp->SetPrevPosition(pos);
}

void WeaponComponent::_FireDoubleBarrel()
{
	GameObject * leftBullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);
	GameObject * rightBullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);

	TransformComponent * leftBulletTComp = static_cast<TransformComponent*>(leftBullet->Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent * leftBulletPComp = static_cast<PhysicsComponent*>(leftBullet->Get(COMPONENT_TYPE::PHYSICS));

	TransformComponent * rightBulletTComp = static_cast<TransformComponent*>(rightBullet->Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent * rightBulletPComp = static_cast<PhysicsComponent*>(rightBullet->Get(COMPONENT_TYPE::PHYSICS));

	TransformComponent * gunTComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));

	if (!leftBulletTComp || !leftBulletPComp || !rightBulletTComp || !rightBulletPComp || !gunTComp)
		return;

	float offset = 16.f;
	Vector3D leftOffset = gunTComp->GetPosition() + Vector3D(offset, 0, 0);
	Vector3D rightOffset = gunTComp->GetPosition() - Vector3D(offset, 0, 0);
	
	
	leftBulletTComp->SetPosition(leftOffset);
	leftBulletTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ());

	leftBulletPComp->SetPosition(leftOffset);
	leftBulletPComp->SetPrevPosition(leftOffset);


	rightBulletTComp->SetPosition(rightOffset);
	rightBulletTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ());

	rightBulletPComp->SetPosition(rightOffset);
	rightBulletPComp->SetPrevPosition(rightOffset);
}

void WeaponComponent::_FireSplitBarrel()
{
	GameObject * leftBullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);
	GameObject * rightBullet = GameObjectManager::GetInstance().SpawnGameObject(m_bulletType);

	TransformComponent * leftBulletTComp = static_cast<TransformComponent*>(leftBullet->Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent * leftBulletPComp = static_cast<PhysicsComponent*>(leftBullet->Get(COMPONENT_TYPE::PHYSICS));

	TransformComponent * rightBulletTComp = static_cast<TransformComponent*>(rightBullet->Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent * rightBulletPComp = static_cast<PhysicsComponent*>(rightBullet->Get(COMPONENT_TYPE::PHYSICS));

	TransformComponent * gunTComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));

	if (!leftBulletTComp || !leftBulletPComp || !rightBulletTComp || !rightBulletPComp || !gunTComp)
		return;

	float offset = 16.f;
	Vector3D leftOffset = gunTComp->GetPosition() + Vector3D(offset, 0, 0);
	Vector3D rightOffset = gunTComp->GetPosition() - Vector3D(offset, 0, 0);


	leftBulletTComp->SetPosition(leftOffset);
	leftBulletTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ() - 45.f);

	leftBulletPComp->SetPosition(leftOffset);
	leftBulletPComp->SetPrevPosition(leftOffset);


	rightBulletTComp->SetPosition(rightOffset);
	rightBulletTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ() + 45.f);

	rightBulletPComp->SetPosition(rightOffset);
	rightBulletPComp->SetPrevPosition(rightOffset);
}

WeaponComponent::WeaponComponent(GameObject & parent, WeaponType weaponType, double rateOfFire, String bulletType, unsigned int burstAmount) :
	Component(parent, COMPONENT_TYPE::WEAPON),
	m_weaponType(weaponType),
	m_rateOfFire(rateOfFire),
	m_bulletType(bulletType),
	m_burstAmount(burstAmount),
	m_timeSinceLastFired(0.0)
{}

WeaponComponent::WeaponComponent(const WeaponComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::WEAPON),
	m_weaponType(rhs.m_weaponType),
	m_rateOfFire(rhs.m_rateOfFire),
	m_bulletType(rhs.m_bulletType),
	m_burstAmount(rhs.m_burstAmount),
	m_timeSinceLastFired(rhs.m_timeSinceLastFired)
{}

WeaponComponent::~WeaponComponent(){}

void WeaponComponent::Update(double deltaTime)
{
	if (m_timeSinceLastFired < m_rateOfFire)
		m_timeSinceLastFired += deltaTime;
}

WeaponComponent * WeaponComponent::Clone(GameObject & parent)
{
	WeaponComponent* comp = new WeaponComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * WeaponComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	String type = AcryJson::ParseString(j, "weapon", "type");
	WeaponType weaponType;

	if (type == "doubleBarrel")
		weaponType = WeaponType::DOUBLE_BARREL;
	else if (type == "splitBarrel")
		weaponType = WeaponType::SPLIT_BARREL;
	else 
		weaponType = WeaponType::SINGLE_BARREL;

	WeaponComponent* comp = new WeaponComponent(gObject,
		weaponType,
		AcryJson::ParseDouble(j, "weapon", "rateOfFire"),
		AcryJson::ParseString(j, "weapon", "bullet"),
		AcryJson::ValueExists(j, "weapon", "burst") ? AcryJson::ParseInt(j, "weapon", "burst") : 1
	);
	comp->_ParseEvents(j, "weapon");
	return comp;
}

void WeaponComponent::Override(nlohmann::json j)
{
	String type = AcryJson::ParseString(j, "weapon", "type");

	if (type == "doubleBarrel")
		m_weaponType = WeaponType::DOUBLE_BARREL;
	else if (type == "splitBarrel")
		m_weaponType = WeaponType::SPLIT_BARREL;
	else
		m_weaponType = WeaponType::SINGLE_BARREL;

	m_rateOfFire = AcryJson::ValueExists(j, "weapon", "rateOfFire") ? AcryJson::ParseDouble(j, "weapon", "rateOfFire") : m_rateOfFire;
	m_bulletType = AcryJson::ValueExists(j, "weapon", "bullet") ? AcryJson::ParseString(j, "weapon", "bullet") : m_bulletType;
	m_burstAmount = AcryJson::ValueExists(j, "weapon", "burst") ? AcryJson::ParseInt(j, "weapon", "burst") : m_burstAmount;

	_ParseEvents(j, "weapon");
	_SubscribeToEvents(this->m_eventsToSubscribeTo);
}

void WeaponComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::PICKUP:
	{
		PickupEvent * pEvent = static_cast<PickupEvent*>(aEvent);
		
		switch (pEvent->PickupType()) {
		case PICKUP_TYPE::DOUBLE_BARREL:
			m_weaponType = WeaponType::DOUBLE_BARREL;
			break;
		case PICKUP_TYPE::SPLIT_BARREL:
			m_weaponType = WeaponType::SPLIT_BARREL;
			break;
		}
	}
	break;
	}
}

void WeaponComponent::Fire()
{
	if (m_timeSinceLastFired >= m_rateOfFire) {
		m_timeSinceLastFired = 0.f;
		
		switch (m_weaponType){
		case WeaponType::SINGLE_BARREL:
				_FireSingleBarrel();
				break;
		case WeaponType::DOUBLE_BARREL:
			_FireDoubleBarrel();
			break;
		case WeaponType::SPLIT_BARREL:
			_FireSplitBarrel();
			break;
		}
	}
}
