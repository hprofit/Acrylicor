#include "PhysicsBodyComponent.h"


PhysicsBodyComponent::PhysicsBodyComponent(GameObject& parent) :
	Component(parent, CT_PHYSICS_BODY)
{}

PhysicsBodyComponent::PhysicsBodyComponent(const PhysicsBodyComponent & rhs, GameObject & parent) :
	Component(parent, CT_PHYSICS_BODY)
{
}


PhysicsBodyComponent::~PhysicsBodyComponent()
{ }

void PhysicsBodyComponent::Update(double deltaTime)
{
}

PhysicsBodyComponent * PhysicsBodyComponent::Clone(GameObject & parent)
{
	return new PhysicsBodyComponent(*this, parent);
}
