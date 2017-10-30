#include "PhysicsManager.h"
#include <algorithm>

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::AddComponent(Component * comp)
{
	m_physicsComponents.push_back(comp);
}

void PhysicsManager::RemoveComponent(Component * comp)
{
	std::vector<Component*>::iterator position = std::find(m_physicsComponents.begin(), m_physicsComponents.end(), comp);
	if (position != m_physicsComponents.end())
		m_physicsComponents.erase(position);
}
