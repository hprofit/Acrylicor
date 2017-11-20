#include "PhysicsManager.h"
#include <algorithm>
#include "Math2D.h"
#include "Math3D.h"
#include "EventManager.h"
#include "CollideEvent.h"

#pragma region Circle on X
static bool CircleOnCircle(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	Circle* lhsC = static_cast<Circle*>(lhs.GetBodyPtr());
	Circle* rhsC = static_cast<Circle*>(rhs.GetBodyPtr());

	unsigned int statics = lhs.IsStatic() + (rhs.IsStatic() * 2);

	switch (statics) {
	case 0:	// Both are non-static
		return AnimatedCircletoAnimatedCircleWillCollideThisFrame(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsPos1, rhsC->m_radius);
	case 1:	// LHS is static
		return AnimatedCircleToStaticCircle(rhsPos0, rhsPos1, rhsC->m_radius, lhsPos0, lhsC->m_radius, Vector3D()) > 0.f;
	case 2:	// RHS is static
		return AnimatedCircleToStaticCircle(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_radius, Vector3D()) > 0.f;
	default: // Both are static
		return StaticCircleToStaticCircle(lhsPos0, lhsC->m_radius, rhsPos0, rhsC->m_radius);
	}

	//if (!lhs.IsStatic() && !rhs.IsStatic())
	//	return AnimatedCircletoAnimatedCircleWillCollideThisFrame(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsPos1, rhsC->m_radius);
	//else if (lhs.IsStatic() && rhs.IsStatic())
	//	return StaticCircleToStaticCircle(lhsPos0, lhsC->m_radius, rhsPos0, rhsC->m_radius);
	//// TODO: revamp collision events to contain impact points and times
	//else if (lhs.IsStatic())
	//	return AnimatedCircleToStaticCircle(rhsPos0, rhsPos1, rhsC->m_radius, lhsPos0, lhsC->m_radius, Vector3D()) > 0.f;
	//else if (rhs.IsStatic())
	//	return AnimatedCircleToStaticCircle(rhsPos0, rhsPos1, rhsC->m_radius, lhsPos0, lhsC->m_radius, Vector3D()) > 0.f;
}

static bool CircleOnAABB(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	Circle* lhsC = static_cast<Circle*>(lhs.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(rhs.GetBodyPtr());

	unsigned int statics = 0;// lhs.IsStatic() + (rhs.IsStatic() * 2);
	switch (statics) {
	case 0:	// Both are non-static
	{
		if (!AnimatedCircletoAnimatedCircleWillCollideThisFrame(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsPos1, rhsC->m_diagonal))
			return false;
		else {
			bool res = AnimatedCircleToStaticRectWillCollideThisFrame(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_halfWidth, rhsC->m_halfHeight, rhsC->m_rect); // Should be moved to next case
			return res;
		}
	}
		break;
	//case 1:	// LHS is static
	//	return AnimatedCircleToStaticCircle(rhsPos0, rhsPos1, rhsC->m_radius, lhsPos0, lhsC->m_radius, Vector3D()) > 0.f;
	//case 2:	// RHS is static
	//	return AnimatedCircleToStaticCircle(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_radius, Vector3D()) > 0.f;
	//case 3: // Both are static
	//	return StaticCircleToStaticCircle(lhsPos0, lhsC->m_radius, rhsPos0, rhsC->m_radius);
	}
}
#pragma endregion

#pragma region AABB on X
static bool AABBOnCircle(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	return CircleOnAABB(rhs, rhsPos0, rhsPos1, lhs, lhsPos0, lhsPos1);
}

static bool AABBOnAABB(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	AABB* lhsC = static_cast<AABB*>(lhs.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(rhs.GetBodyPtr());
	// TODO: update this with animated checks
	return StaticRectToStaticRect(lhsPos0, lhsC->m_halfWidth, lhsC->m_halfWidth, rhsPos0, rhsC->m_halfWidth, rhsC->m_halfWidth);
}
#pragma endregion

PhysicsManager::PhysicsManager() :
	_EventManager(EventManager::GetInstance())
{
	m_collisionFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_CIRCLE] = CircleOnCircle;
	m_collisionFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_AABB] = CircleOnAABB;

	m_collisionFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_CIRCLE] = AABBOnCircle;
	m_collisionFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_AABB] = AABBOnAABB;
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::_RemoveBody(Component * comp)
{
	std::vector<Component*>::iterator position = std::find(m_physicsBodies.begin(), m_physicsBodies.end(), comp);
	if (position != m_physicsBodies.end())
		m_physicsBodies.erase(position);
}

void PhysicsManager::_RemoveTransform(Component * comp)
{
	std::vector<Component*>::iterator position = std::find(m_transforms.begin(), m_transforms.end(), comp);
	if (position != m_transforms.end())
		m_transforms.erase(position);
}

void PhysicsManager::AddComponent(Component * comp)
{
	if (comp->m_type == COMPONENT_TYPE::PHYSICS)
		m_physicsBodies.push_back(comp);
	else if (comp->m_type ==COMPONENT_TYPE::TRANSFORM)
		m_transforms.push_back(comp);
}

void PhysicsManager::RemoveComponent(Component * comp)
{
	if (comp->m_type == COMPONENT_TYPE::PHYSICS)
		_RemoveBody(comp);
	else if (comp->m_type ==COMPONENT_TYPE::TRANSFORM)
		_RemoveTransform(comp);
}

void PhysicsManager::UpdatePhysics(double deltaTime)
{
	_ResetContacts();

	unsigned int i = 0;
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

			unsigned int j = i;
			for (j = i; j < m_physicsBodies.size(); ++j) {
				if (i == j)
					continue;
				if (m_physicsBodies[j] && m_physicsBodies[j]->m_parent.IsActive()) {
					PhysicsComponent* rhs = static_cast<PhysicsComponent*>(m_physicsBodies[j]);
					
					if (_CheckCollision(*lhs, *rhs))
						_CreateContact(&lhs->m_parent, &rhs->m_parent);
				}
			}
		}
	}

	// Process contacts
	for (i = 0; i < m_contacts.size(); ++i) {
		CollideEvent * cEvent = new CollideEvent(0.0, m_contacts[i]->LHS_GO(), m_contacts[i]->RHS_GO());
		m_contacts[i]->LHS_GO()->HandleEvent(cEvent);
		m_contacts[i]->RHS_GO()->HandleEvent(cEvent);
	}
}

void PhysicsManager::_CreateContact(GameObject* lhsGO, GameObject* rhsGO)
{
	m_contacts.push_back(new Contact(lhsGO, rhsGO));
}

void PhysicsManager::_ResetContacts()
{
	for (unsigned int i = 0; i < m_contacts.size(); ++i) {
		if (m_contacts[i])
			delete m_contacts[i];
	}
	m_contacts.clear();
}

bool PhysicsManager::_CheckCollision(const PhysicsComponent & lhs, const PhysicsComponent & rhs)
{
	return m_collisionFunctions[lhs.Body().m_type][rhs.Body().m_type](
		lhs, lhs.GetPrevPosition(), lhs.GetPosition(),
		rhs, rhs.GetPrevPosition(), rhs.GetPosition());
}


