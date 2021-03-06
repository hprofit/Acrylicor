#include "PhysicsManager.h"
#include <algorithm>
#include "Math2D.h"
#include "Math3D.h"
#include "EventManager.h"
#include "CollideEvent.h"

#include <iostream>

#pragma region Collision Methods

#pragma region Circle on X
static CollisionResult CircleOnCircle(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	Circle* lhsC = static_cast<Circle*>(lhs.GetBodyPtr());
	Circle* rhsC = static_cast<Circle*>(rhs.GetBodyPtr());

	unsigned int statics = lhs.IsStatic() + (rhs.IsStatic() * 2);

	switch (statics) {
	case 0:	// Both are non-static
		return AnimatedCircleToAnimatedCircle(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsPos1, rhsC->m_radius);
	case 1:	// LHS is static
		return AnimatedCircleToStaticCircle(rhsPos0, rhsPos1, rhsC->m_radius, lhsPos0, lhsC->m_radius);
	case 2:	// RHS is static
		return AnimatedCircleToStaticCircle(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_radius);
	default: // Both are static
		return CollisionResult(StaticCircleToStaticCircle(lhsPos0, lhsC->m_radius, rhsPos0, rhsC->m_radius));
	}
}

static CollisionResult CircleOnAABB(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	Circle* lhsC = static_cast<Circle*>(lhs.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(rhs.GetBodyPtr());

	return AnimatedCircleToStaticRect(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_halfWidth, rhsC->m_halfHeight, rhsC->m_rect);

	//unsigned int statics = 0;// lhs.IsStatic() + (rhs.IsStatic() * 2);
	//switch (statics) {
	//case 0:	// Both are non-static
	//{
		//return AnimatedCircleToStaticRect(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_halfWidth, rhsC->m_halfHeight, rhsC->m_rect);
	//}
	//	break;
	//case 1:	// LHS is static
	//	return AnimatedCircleToStaticCircle(rhsPos0, rhsPos1, rhsC->m_radius, lhsPos0, lhsC->m_radius, Vector3D()) > 0.f;
	//case 2:	// RHS is static
	//	return AnimatedCircleToStaticCircle(lhsPos0, lhsPos1, lhsC->m_radius, rhsPos0, rhsC->m_radius, Vector3D()) > 0.f;
	//default: // Both are static
	//	return StaticCircleToStaticCircle(lhsPos0, lhsC->m_radius, rhsPos0, rhsC->m_radius);
	//}
}
#pragma endregion

#pragma region AABB on X
static CollisionResult AABBOnCircle(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	return CircleOnAABB(rhs, rhsPos0, rhsPos1, lhs, lhsPos0, lhsPos1);
}

static CollisionResult AABBOnAABB(const PhysicsComponent & lhs, Vector3D lhsPos0, Vector3D lhsPos1, const PhysicsComponent & rhs, Vector3D rhsPos0, Vector3D rhsPos1) {
	AABB* lhsC = static_cast<AABB*>(lhs.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(rhs.GetBodyPtr());
	// TODO: update this with animated checks
	return CollisionResult(StaticRectToStaticRect(lhsPos0, lhsC->m_halfWidth, lhsC->m_halfHeight, rhsPos0, rhsC->m_halfWidth, rhsC->m_halfHeight));
}
#pragma endregion

#pragma endregion

#pragma region Reflection Methods

#pragma region Circle on X
static Vector3D ReflectCircleOnCircle(const PhysicsComponent & compToReflect, const PhysicsComponent & reflectionSurface, const CollisionResult& cr) {
	Circle* lhsC = static_cast<Circle*>(compToReflect.GetBodyPtr());
	Circle* rhsC = static_cast<Circle*>(reflectionSurface.GetBodyPtr());

	return ReflectAnimatedCircleOnStaticCircle(compToReflect.GetPrevPosition(), compToReflect.GetPosition(), lhsC->m_radius, reflectionSurface.GetPositionAtTime(cr.timeOfImpact), rhsC->m_radius, cr);
}

static Vector3D ReflectCircleOnAABB(const PhysicsComponent & compToReflect, const PhysicsComponent & reflectionSurface, const CollisionResult& cr) {
	Circle* lhsC = static_cast<Circle*>(compToReflect.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(reflectionSurface.GetBodyPtr());

	return ReflectAnimatedCircleOnStaticRect(compToReflect.GetPosition(), compToReflect.GetPositionAtTime(cr.timeOfImpact), reflectionSurface.GetPositionAtTime(cr.timeOfImpact), rhsC->m_halfWidth, rhsC->m_halfHeight, rhsC->m_rect);
}
#pragma endregion

#pragma region AABB on X
static Vector3D ReflectAABBOnCircle(const PhysicsComponent & compToReflect, const PhysicsComponent & reflectionSurface, const CollisionResult& cr) {
	//AABB* lhsC = static_cast<AABB*>(compToReflect.GetBodyPtr());
	//Circle* rhsC = static_cast<Circle*>(reflectionSurface.GetBodyPtr());
	//return ReflectAnimatedRectOnStaticCircle();

	return ReflectCircleOnAABB(reflectionSurface, compToReflect, cr);
}

static Vector3D ReflectAABBOnAABB(const PhysicsComponent & compToReflect, const PhysicsComponent & reflectionSurface, const CollisionResult& cr) {
	AABB* lhsC = static_cast<AABB*>(compToReflect.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(reflectionSurface.GetBodyPtr());
	// TODO: update this with animated checks
	return Vector3D();
	//return StaticRectToStaticRect(lhsPos0, lhsC->m_halfWidth, lhsC->m_halfHeight, rhsPos0, rhsC->m_halfWidth, rhsC->m_halfHeight);
	//return ReflectAnimatedRectOnStaticRect();
}
#pragma endregion

#pragma endregion

#pragma region Push Methods

#pragma region Circle on X
static Vector3D PushCircleFromCircle(const PhysicsComponent & compToPush, const PhysicsComponent & surface, const Vector3D & poi, const CollisionResult& cr) {
	Circle* lhsC = static_cast<Circle*>(compToPush.GetBodyPtr());
	Circle* rhsC = static_cast<Circle*>(surface.GetBodyPtr());

	return PushCircleFromCircle(lhsC->m_radius, rhsC->m_radius, poi, cr);
}

static Vector3D PushCircleFromAABB(const PhysicsComponent & compToPush, const PhysicsComponent & surface, const Vector3D & poi, const CollisionResult& cr) {
	Circle* lhsC = static_cast<Circle*>(compToPush.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(surface.GetBodyPtr());

	return PushCircleFromRect(compToPush.GetPosition(), lhsC->m_radius,
		surface.GetPositionAtTime(cr.timeOfImpact), rhsC->m_halfWidth, rhsC->m_halfHeight, cr);
}
#pragma endregion

#pragma region AABB on X
static Vector3D PushAABBFromCircle(const PhysicsComponent & compToPush, const PhysicsComponent & surface, const Vector3D & poi, const CollisionResult& cr) {
	return PushCircleFromAABB(surface, compToPush, poi,  cr);
}

static Vector3D PushAABBFromAABB(const PhysicsComponent & compToPush, const PhysicsComponent & surface, const Vector3D & poi, const CollisionResult& cr) {
	AABB* lhsC = static_cast<AABB*>(compToPush.GetBodyPtr());
	AABB* rhsC = static_cast<AABB*>(surface.GetBodyPtr());
	// TODO: Flesh this out
	return Vector3D();
}
#pragma endregion

#pragma endregion




PhysicsManager::PhysicsManager() :
	_EventManager(EventManager::GetInstance())
{
	m_collisionFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_CIRCLE] = CircleOnCircle;
	m_collisionFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_AABB] = CircleOnAABB;

	m_collisionFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_CIRCLE] = AABBOnCircle;
	m_collisionFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_AABB] = AABBOnAABB;



	m_reflectionFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_CIRCLE] = ReflectCircleOnCircle;
	m_reflectionFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_AABB] = ReflectCircleOnAABB;

	m_reflectionFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_CIRCLE] = ReflectAABBOnCircle;
	m_reflectionFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_AABB] = ReflectAABBOnAABB;



	m_pushFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_CIRCLE] = PushCircleFromCircle;
	m_pushFunctions[BODY_TYPE::BT_CIRCLE][BODY_TYPE::BT_AABB] = PushCircleFromAABB;

	m_pushFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_CIRCLE] = PushAABBFromCircle;
	m_pushFunctions[BODY_TYPE::BT_AABB][BODY_TYPE::BT_AABB] = PushAABBFromAABB;

	_AddSubscriberToTracker();
	SubscribeToEvent(EventType::UNLOAD_LEVEL);
}

PhysicsManager::~PhysicsManager(){}

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

void PhysicsManager::_RemoveAll()
{
	m_physicsBodies.clear();
	m_transforms.clear();
}

void PhysicsManager::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::UNLOAD_LEVEL:
	{
		_RemoveAll();
	}
	break;
	}
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

	// Update Physics Bodies
	std::for_each(m_physicsBodies.begin(), m_physicsBodies.end(), [&deltaTime](Component* body) {
		if (body && body->m_parent.IsActive())
			body->Update(deltaTime);
	});


	// Check for collisions
	CollisionResult cr;
	unsigned int i = 0;
	for (i = 0; i < m_physicsBodies.size(); ++i) {
		if (m_physicsBodies[i] && m_physicsBodies[i]->m_parent.IsActive()) {
			PhysicsComponent* lhs = static_cast<PhysicsComponent*>(m_physicsBodies[i]);

			unsigned int j = i+1;
			for (j = i+1; j < m_physicsBodies.size(); ++j) {
				if (i == j)
					continue;
				if (m_physicsBodies[j] && m_physicsBodies[j]->m_parent.IsActive()) {
					PhysicsComponent* rhs = static_cast<PhysicsComponent*>(m_physicsBodies[j]);
					cr = _CheckCollision(*lhs, *rhs);
					if (cr.collided) {
						_CreateContact(&lhs->m_parent, &rhs->m_parent, cr);
					}
				}
			}
		}
	}

	// Process contacts
	std::for_each(m_contacts.begin(), m_contacts.end(), [](Contact* contact) {
		CollideEvent * cEvent = new CollideEvent(*contact);
		contact->LHS_GO()->HandleEvent(cEvent);
		contact->RHS_GO()->HandleEvent(cEvent);
	});

	// Update Physics Bodies
	std::for_each(m_physicsBodies.begin(), m_physicsBodies.end(), [](Component* body) {
		if (body && body->m_parent.IsActive())
			body->LateUpdate();
	});

	// Update Transforms
	std::for_each(m_transforms.begin(), m_transforms.end(), [&deltaTime](Component* transform) {
		if (transform && transform->m_parent.IsActive())
			transform->Update(deltaTime);
	});
}

void PhysicsManager::_CreateContact(GameObject* lhsGO, GameObject* rhsGO, CollisionResult collision)
{
	m_contacts.push_back(new Contact(lhsGO, rhsGO, collision));
}

void PhysicsManager::_ResetContacts()
{
	for (unsigned int i = 0; i < m_contacts.size(); ++i) {
		if (m_contacts[i])
			delete m_contacts[i];
	}
	m_contacts.clear();
}

CollisionResult PhysicsManager::_CheckCollision(const PhysicsComponent & lhs, const PhysicsComponent & rhs)
{
	return m_collisionFunctions[lhs.Body().m_type][rhs.Body().m_type](
		lhs, lhs.GetPrevPosition(), lhs.GetPosition(),
		rhs, rhs.GetPrevPosition(), rhs.GetPosition());
}

Vector3D PhysicsManager::ReflectShapeOffOtherShape(const PhysicsComponent & lhs, const PhysicsComponent & rhs, const CollisionResult& cr) 
{
	return m_reflectionFunctions[lhs.Body().m_type][rhs.Body().m_type](lhs, rhs, cr);
}

Vector3D PhysicsManager::PushShapeOutOfOtherShape(const PhysicsComponent & lhs, const PhysicsComponent & rhs, const Vector3D & poi, const CollisionResult & cr)
{
	return m_pushFunctions[lhs.Body().m_type][rhs.Body().m_type](lhs, rhs, poi, cr);
}
