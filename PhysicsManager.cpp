#include "PhysicsManager.h"
#include <algorithm>
#include "Math2D.h"

PhysicsManager::PhysicsManager()
{
	// TODO: Hook up collision functions
	
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::RemoveBody(Component * comp)
{
	std::vector<Component*>::iterator position = std::find(m_physicsBodies.begin(), m_physicsBodies.end(), comp);
	if (position != m_physicsBodies.end())
		m_physicsBodies.erase(position);
}

void PhysicsManager::RemoveTransform(Component * comp)
{
	std::vector<Component*>::iterator position = std::find(m_transforms.begin(), m_transforms.end(), comp);
	if (position != m_transforms.end())
		m_transforms.erase(position);
}

void PhysicsManager::AddComponent(Component * comp)
{
	if (comp->m_type == CT_PHYSICS)
		m_physicsBodies.push_back(comp);
	else if (comp->m_type == CT_TRANSFORM)
		m_transforms.push_back(comp);
}

void PhysicsManager::RemoveComponent(Component * comp)
{
	if (comp->m_type == CT_PHYSICS)
		RemoveBody(comp);
	else if (comp->m_type == CT_TRANSFORM)
		RemoveTransform(comp);
}

void PhysicsManager::UpdatePhysics(double deltaTime)
{
	ResetContacts();

	int i = 0;
	// Update Physics Bodies
	for (i = 0; i < m_physicsBodies.size(); ++i) {
		if (m_physicsBodies[i] && m_physicsBodies[i]->m_parent.IsActive())
			m_physicsBodies[i]->Update(deltaTime);
	}
	// Update Transforms
	for (i = 0; i < m_transforms.size(); ++i) {
		if (m_transforms[i] && m_transforms[i]->m_parent.IsActive())
			m_transforms[i]->Update(deltaTime);
	}
	// Check for collisions
	for (i = 0; i < m_physicsBodies.size(); ++i) {
		if (m_physicsBodies[i] && m_physicsBodies[i]->m_parent.IsActive()) {
			PhysicsComponent* lhs = static_cast<PhysicsComponent*>(m_physicsBodies[i]);

			int j = 0;
			for (j = 0; j < m_physicsBodies.size(); ++j) {
				if (i == j)
					continue;
				if (m_physicsBodies[j] && m_physicsBodies[j]->m_parent.IsActive()) {
					PhysicsComponent* rhs = static_cast<PhysicsComponent*>(m_physicsBodies[j]);
					
					if (CheckCollision(lhs->Body(), lhs->GetPosition(), rhs->Body(), rhs->GetPosition()))
						CreateContact(&lhs->Body(), &rhs->Body());
				}
			}
		}
	}
}

void PhysicsManager::CreateContact(PhysicsBody * lhs, PhysicsBody * rhs)
{
	m_contacts.push_back(new Contact(lhs, rhs));
}

void PhysicsManager::ResetContacts()
{
	for (int i = 0; i < m_contacts.size(); ++i) {
		if (m_contacts[i])
			delete m_contacts[i];
	}
	m_contacts.clear();
}

bool PhysicsManager::CheckCollision(PhysicsBody & lhs, Vector3D lhsPos, PhysicsBody & rhs, Vector3D rhsPos)
{
	return m_collisionFunctions[lhs.m_type][rhs.m_type](lhs, lhsPos, rhs, rhsPos);
}


