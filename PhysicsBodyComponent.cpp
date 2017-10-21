#include "PhysicsBodyComponent.h"


PhysicsBodyComponent::PhysicsBodyComponent(GameObject& parent) :
	Component(parent, CT_PHYSICS_BODY)
{}


PhysicsBodyComponent::~PhysicsBodyComponent()
{ }

void PhysicsBodyComponent::Update()
{
}
