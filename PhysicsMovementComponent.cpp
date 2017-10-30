#include "PhysicsMovementComponent.h"

PhysicsMovementComponent::PhysicsMovementComponent(GameObject& parent) :
	Component(parent, CT_PHYSICS_MOVEMENT),
	m_velocity(Vector2D()),
	m_acceleration(Vector2D())
{ }

PhysicsMovementComponent::PhysicsMovementComponent(GameObject& parent, Vector2D velocity) :
	Component(parent, CT_PHYSICS_MOVEMENT),
	m_velocity(velocity),
	m_acceleration(Vector2D())
{ }

PhysicsMovementComponent::PhysicsMovementComponent(GameObject& parent, Vector2D velocity, Vector2D acceleration) :
	Component(parent, CT_PHYSICS_MOVEMENT),
	m_velocity(velocity),
	m_acceleration(acceleration)
{ }

PhysicsMovementComponent::PhysicsMovementComponent(const PhysicsMovementComponent& rhs, GameObject & parent) :
	Component(parent, CT_PHYSICS_MOVEMENT),
	m_velocity(rhs.m_velocity),
	m_acceleration(rhs.m_acceleration)
{
}

PhysicsMovementComponent::~PhysicsMovementComponent()
{
}

void PhysicsMovementComponent::Update(double deltaTime)
{
}

PhysicsMovementComponent * PhysicsMovementComponent::Clone(GameObject & parent)
{
	return new PhysicsMovementComponent(*this, parent);
}
