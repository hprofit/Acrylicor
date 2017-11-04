#include "PhysicsComponent.h"
#include "PhysicsManager.h"

PhysicsComponent::PhysicsComponent(GameObject& parent) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(Vector3D()),
	m_acceleration(Vector3D())
{ }

PhysicsComponent::PhysicsComponent(GameObject& parent, Vector3D velocity) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(velocity),
	m_acceleration(Vector3D())
{ }

PhysicsComponent::PhysicsComponent(GameObject& parent, Vector3D velocity, Vector3D acceleration) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(velocity),
	m_acceleration(acceleration)
{ }

PhysicsComponent::PhysicsComponent(const PhysicsComponent& rhs, GameObject & parent) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(rhs.m_velocity),
	m_acceleration(rhs.m_acceleration)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Update(double deltaTime)
{
}

PhysicsComponent * PhysicsComponent::Clone(GameObject & parent)
{
	PhysicsComponent* pComp = new PhysicsComponent(*this, parent);
	pComp->RegisterWithManager();
	return pComp;
}

Component * PhysicsComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new PhysicsComponent(gObject);
}

void PhysicsComponent::Override(nlohmann::json j)
{
}

void PhysicsComponent::RegisterWithManager()
{
	PhysicsManager::GetInstance().AddComponent(this);
}
