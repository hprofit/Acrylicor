#include "PhysicsMovementComponent.h"

PhysicsMovementComponent::PhysicsMovementComponent(GameObject& parent) :
	Component(parent),
	m_velocity(Vector2D()),
	m_acceleration(Vector2D())
{ }

PhysicsMovementComponent::PhysicsMovementComponent(GameObject& parent, Vector2D velocity) :
	Component(parent),
	m_velocity(velocity),
	m_acceleration(Vector2D())
{ }

PhysicsMovementComponent::PhysicsMovementComponent(GameObject& parent, Vector2D velocity, Vector2D acceleration) :
	Component(parent),
	m_velocity(velocity),
	m_acceleration(acceleration)
{ }

PhysicsMovementComponent::~PhysicsMovementComponent()
{
}