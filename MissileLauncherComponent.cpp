#include "MissileLauncherComponent.h"
#include "JsonReader.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "MissileCountChangeEvent.h"
#include "EventManager.h"

MissileLauncherComponent::MissileLauncherComponent(GameObject & parent, int count, double rateOfFire, String missileType) :
	Component(parent, COMPONENT_TYPE::MISSILE_LAUNCHER),
	m_count(count),
	m_rateOfFire(rateOfFire),
	m_timeSinceLastFired(0.0),
	m_missileType(missileType) {}

MissileLauncherComponent::MissileLauncherComponent(const MissileLauncherComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::MISSILE_LAUNCHER),
	m_count(rhs.m_count), 
	m_rateOfFire(rhs.m_rateOfFire), 
	m_timeSinceLastFired(rhs.m_timeSinceLastFired), 
	m_missileType(rhs.m_missileType) {}

MissileLauncherComponent::~MissileLauncherComponent() {}

void MissileLauncherComponent::Update(double deltaTime)
{
	if (m_timeSinceLastFired < m_rateOfFire)
		m_timeSinceLastFired += deltaTime;
}

MissileLauncherComponent * MissileLauncherComponent::Clone(GameObject & parent)
{
	MissileLauncherComponent* comp = new MissileLauncherComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * MissileLauncherComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new MissileLauncherComponent(gObject,
		AcryJson::ParseInt(j, "missileLauncher", "count"),
		AcryJson::ParseDouble(j, "missileLauncher", "rateOfFire"),
		AcryJson::ParseString(j, "missileLauncher", "missile")
	);
}

void MissileLauncherComponent::Override(nlohmann::json j)
{
	m_count = AcryJson::ValueExists(j, "missileLauncher", "count") ? AcryJson::ParseInt(j, "missileLauncher", "count") : m_count;
	m_rateOfFire = AcryJson::ValueExists(j, "missileLauncher", "rateOfFire") ? AcryJson::ParseDouble(j, "missileLauncher", "rateOfFire") : m_rateOfFire;
	m_missileType = AcryJson::ValueExists(j, "missileLauncher", "missile") ? AcryJson::ParseString(j, "missileLauncher", "missile") : m_missileType;
}

void MissileLauncherComponent::HandleEvent(AcryEvent * aEvent)
{

}

void MissileLauncherComponent::LateInitialize()
{
	EventManager::GetInstance().BroadcastEventToSubscribers(new MissileCountChangeEvent(0.0, m_count));
}

int MissileLauncherComponent::Remaining() const
{
	return m_count;
}

void MissileLauncherComponent::Fire()
{
	if (m_timeSinceLastFired >= m_rateOfFire && --m_count >= 0) {
		m_timeSinceLastFired = 0.f;
		GameObject * missile = GameObjectManager::GetInstance().SpawnGameObject(m_missileType);

		TransformComponent * missileTComp = static_cast<TransformComponent*>(missile->Get(COMPONENT_TYPE::TRANSFORM));
		PhysicsComponent * missilePComp = static_cast<PhysicsComponent*>(missile->Get(COMPONENT_TYPE::PHYSICS));

		TransformComponent * gunTComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
		PhysicsComponent * gunPComp = static_cast<PhysicsComponent*>(m_parent.GetImmediate(COMPONENT_TYPE::PHYSICS));

		if (!missileTComp || !missilePComp || !gunTComp)
			return;

		missileTComp->SetPosition(gunTComp->GetPosition());
		missileTComp->SetAngles(gunTComp->GetAngleX(), gunTComp->GetAngleY(), gunTComp->GetAngleZ());

		if (gunPComp) {
			missilePComp->SetPosition(gunPComp->GetPosition());
			missilePComp->SetPrevPosition(gunPComp->GetPrevPosition());
		}
		else {
			missilePComp->SetPosition(gunTComp->GetPosition());
			missilePComp->SetPrevPosition(gunTComp->GetPosition());
		}

		EventManager::GetInstance().BroadcastEventToSubscribers(new AcryEvent(EventType::MISSILE_FIRED));
	}
}
