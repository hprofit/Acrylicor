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
	m_components.push_back(comp);
}

void PhysicsManager::RemoveComponent(Component * comp)
{
	std::vector<Component*>::iterator position = std::find(m_components.begin(), m_components.end(), comp);
	if (position != m_components.end())
		m_components.erase(position);
}

void PhysicsManager::UpdatePhysics(double deltaTime)
{
	int i = 0;
	for (i = 0; i < m_components.size(); ++i) {
		if (m_components[i] && m_components[i]->m_parent.IsActive())
			m_components[i]->Update(deltaTime);
	}
}
