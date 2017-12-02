#include "PhysicsComponent.h"
#include "PhysicsManager.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "JsonReader.h"
#include "Math3D.h"

#include "AcryEvent.h"
#include "CollideEvent.h"
#include "DamageEvent.h"
#include "ReflectEvent.h"
#include "PushFromBodyEvent.h"
#include "CollideKillZoneEvent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "DamageComponent.h"

#include <iostream>

#pragma region Ctor/Dtor
PhysicsComponent::PhysicsComponent(GameObject& parent) :
	Component(parent, COMPONENT_TYPE::PHYSICS, true),
	m_velocity(Vector3D()), m_acceleration(Vector3D()),
	m_position(Vector3D()), m_prevPosition(Vector3D()),
	m_force(Vector3D()),
	m_mass(0.f), m_InvMass(0.f),
	m_weightless(false),
	m_maxSpeed(0.f),
	m_capRate(.99f),
	m_body(nullptr)
{ }

PhysicsComponent::PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity) :
	Component(parent, COMPONENT_TYPE::PHYSICS, true),
	m_velocity(velocity), m_acceleration(Vector3D()),
	m_position(position), m_prevPosition(position),
	m_force(Vector3D()),
	m_mass(0.f), m_InvMass(0.f),
	m_weightless(false),
	m_maxSpeed(0.f),
	m_capRate(.99f),
	m_body(nullptr)
{ }

PhysicsComponent::PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity, Vector3D acceleration) :
	Component(parent, COMPONENT_TYPE::PHYSICS, true),
	m_velocity(velocity), m_acceleration(acceleration),
	m_position(position), m_prevPosition(position),
	m_force(Vector3D()),
	m_mass(0.f), m_InvMass(0.f),
	m_weightless(false),
	m_maxSpeed(0.f),
	m_capRate(.99f),
	m_body(nullptr)
{ }

PhysicsComponent::PhysicsComponent(GameObject & parent, Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float invMass, bool weightless, float maxSpeed, float capRate) :
	Component(parent, COMPONENT_TYPE::PHYSICS, true),
	m_velocity(velocity), m_acceleration(Vector3D()),
	m_position(position), m_prevPosition(position),
	m_force(Vector3D()),
	m_mass(mass), m_InvMass(invMass),
	m_weightless(weightless),
	m_maxSpeed(maxSpeed),
	m_capRate(capRate),
	m_body(nullptr)
{}

PhysicsComponent::PhysicsComponent(const PhysicsComponent& rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::PHYSICS, true),
	m_velocity(rhs.m_velocity), m_acceleration(rhs.m_acceleration),
	m_position(rhs.m_position), m_prevPosition(rhs.m_prevPosition),
	m_force(rhs.m_force),
	m_mass(rhs.m_mass), m_InvMass(rhs.m_InvMass),
	m_weightless(rhs.m_weightless), 
	m_maxSpeed(rhs.m_maxSpeed), 
	m_capRate(rhs.m_capRate),
	m_body(nullptr)
{
	// TODO: Fix this
	switch (rhs.m_body->m_type) {
		case BODY_TYPE::BT_CIRCLE:
			m_body = new Circle(*static_cast<Circle*>(rhs.m_body));
			break;
		case BODY_TYPE::BT_AABB:
			m_body = new AABB(*static_cast<AABB*>(rhs.m_body));
			break;
	}
}

PhysicsComponent::~PhysicsComponent()
{
	PhysicsManager::GetInstance().RemoveComponent(this);
}
#pragma endregion

void PhysicsComponent::Update(double deltaTime)
{
	Update(deltaTime, 0.f);
}

void PhysicsComponent::Update(double deltaTime, float gravity)
{
	m_prevPosition = m_position;
	if (!m_weightless) {
		m_force -= Vector3D(1.f, 1.f, 1.f) * gravity;

		m_acceleration = m_force * m_InvMass;

		m_velocity = ((m_acceleration * (float)deltaTime) + m_velocity) * m_capRate;
	}

	if (m_velocity.SquareLength() > (m_maxSpeed * m_maxSpeed)) {
		m_velocity = Vector3D::Normalize(m_velocity) * m_maxSpeed;
	}

	m_position += m_velocity * (float)deltaTime;

	m_force = Vector3D();
}

void PhysicsComponent::LateUpdate()
{
	m_tComp->SetPosition(m_position);
}

PhysicsComponent * PhysicsComponent::Clone(GameObject & parent)
{
	PhysicsComponent* pComp = new PhysicsComponent(*this, parent);
	pComp->RegisterWithManager();
	pComp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return pComp;
}

Component * PhysicsComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	Vector3D position = AcryJson::ParseVector3D(j, "physics", "position");
	Vector3D velocity = AcryJson::ParseVector3D(j, "physics", "velocity");
	Vector3D acceleration = AcryJson::ParseVector3D(j, "physics", "acceleration");
	float mass = AcryJson::ParseFloat(j, "physics", "mass");
	float invMass = mass != 0.f ? 1.f / mass : 0.f;
	bool weightless = AcryJson::ParseBool(j, "physics", "weightless");
	float maxSpeed = AcryJson::ParseFloat(j, "physics", "maxSpeed");
	float capRate = AcryJson::ValueExists(j, "physics", "capRate") ? AcryJson::ParseFloat(j, "physics", "capRate") : 0.99f;

	PhysicsBody * pBody = nullptr;
	String bodyTypeString = AcryJson::ParseString(j, "physics", "body", "type");
	if (bodyTypeString.compare("circle") == 0)
		pBody = new Circle(AcryJson::ParseFloat(j, "physics", "body", "radius"));
	else if (bodyTypeString.compare("aabb") == 0) {
		pBody = new AABB(
			AcryJson::ParseFloat(j, "physics", "body", "width"),
			AcryJson::ParseFloat(j, "physics", "body", "height")
		);
	}

	PhysicsComponent * pComp = new PhysicsComponent(gObject, position, velocity, acceleration, mass, invMass, weightless, maxSpeed, capRate);
	pComp->m_body = pBody;
	if (AcryJson::ValueExists(j, "physics", "body", "tags"))
		pBody->Tags().SetTags(j["physics"]["body"]["tags"]);

	pComp->m_static = AcryJson::ParseBool(j, "physics", "static");

	return pComp;
}

void PhysicsComponent::Override(nlohmann::json j)
{
	m_position = AcryJson::ValueExists(j, "physics", "position") ? AcryJson::ParseVector3D(j, "physics", "position") : m_position;
	m_prevPosition = m_position;
	m_velocity = AcryJson::ValueExists(j, "physics", "velocity") ? AcryJson::ParseVector3D(j, "physics", "velocity") : m_velocity;
	m_acceleration = AcryJson::ValueExists(j, "physics", "acceleration") ? AcryJson::ParseVector3D(j, "physics", "acceleration") : m_acceleration;
	m_mass = AcryJson::ValueExists(j, "physics", "mass") ? AcryJson::ParseFloat(j, "physics", "mass") : m_mass;
	float invMass = m_mass != 0.f ? 1.f / m_mass : 0.f;
	m_weightless = AcryJson::ValueExists(j, "physics", "weightless") ? AcryJson::ParseBool(j, "physics", "weightless") : m_weightless;
	m_maxSpeed = AcryJson::ValueExists(j, "physics", "weightless") ? AcryJson::ParseFloat(j, "physics", "maxSpeed") : m_maxSpeed;
	m_capRate = AcryJson::ValueExists(j, "physics", "capRate") ? AcryJson::ParseFloat(j, "physics", "capRate") : m_capRate;

	PhysicsBody * pBody = nullptr;
	String bodyTypeString = AcryJson::ParseString(j, "physics", "body", "type");
	if (bodyTypeString.compare("circle") == 0)
		pBody = new Circle(AcryJson::ParseFloat(j, "physics", "body", "radius"));
	else if (bodyTypeString.compare("aabb") == 0) 
		pBody = new AABB(
			AcryJson::ParseFloat(j, "physics", "body", "width"),
			AcryJson::ParseFloat(j, "physics", "body", "height")
		);

	if (pBody) {
		std::list<String> tags = m_body->Tags().GetTags();
		m_body = pBody;
		m_body->Tags().SetTags(tags);
		if (AcryJson::ValueExists(j, "physics", "body", "tags"))
			m_body->Tags().SetTags(j["physics"]["body"]["tags"]);
	}

	m_static = AcryJson::ValueExists(j, "physics", "static") ? AcryJson::ParseBool(j, "physics", "static") : m_static;
}

void PhysicsComponent::RegisterWithManager()
{
	PhysicsManager::GetInstance().AddComponent(this);
}

void PhysicsComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::COLLIDE:
	{
		CollideEvent * cpEvent = static_cast<CollideEvent*>(aEvent);


		GameObject * other = cpEvent->GetContact().LHS_GO()->Get(COMPONENT_TYPE::PHYSICS) == this ?
			cpEvent->GetContact().RHS_GO() : cpEvent->GetContact().LHS_GO();
		PhysicsComponent * otherPComp = static_cast<PhysicsComponent*>(other->Get(COMPONENT_TYPE::PHYSICS));


		// TODO: Should be scripted stuff

		// Kill Zone
		if (m_body->Tags().HasTag("killZone")) {
			m_parent.HandleEvent(new CollideKillZoneEvent(0.0, other));
		}
		// Enemy on Enemy -- No Pass
		else if ((m_body->Tags().HasTag("enemy") && otherPComp->Body().Tags().HasTag("enemy")) && 
			m_body->Tags().HasTag("noPass")) {
			PushFromBodyEvent * rEvent = new PushFromBodyEvent(cpEvent->GetContact());
			m_parent.HandleEvent(rEvent);
		}
		// Solid on Solid
		else if (m_body->Tags().HasTag("solid") && otherPComp->Body().Tags().HasTag("solid")) {
			PushFromBodyEvent * rEvent = new PushFromBodyEvent(cpEvent->GetContact());
			m_parent.HandleEvent(rEvent);
			other->HandleEvent(rEvent);
		}
		// Player
		else if (m_body->Tags().HasTag("player")) {
			if ((otherPComp->Body().Tags().HasTag("enemy") || otherPComp->Body().Tags().HasTag("enemyBullet"))) {
				EventManager::GetInstance().BroadcastEventToSubscribers(new AcryEvent(EventType::PLAYER_DEATH));
				EventManager::GetInstance().AddDelayedEvent(new AcryEvent(EventType::RESPAWN, 3.0));

				GameObjectManager::GetInstance().DestroyGameObject(&m_parent);
				GameObjectManager::GetInstance().DestroyGameObject(other);
			}
			else if (otherPComp->Body().Tags().HasTag("solid")) {
				
			}
		}
		// Player Bullet on Enemy
		else if (m_body->Tags().HasTag("playerBullet") && otherPComp->Body().Tags().HasTag("enemy")) {
			DamageComponent * dComp = static_cast<DamageComponent*>(m_parent.Get(COMPONENT_TYPE::DAMAGE));
			other->HandleEvent(new DamageEvent(0.0, dComp->Amount()));

			// TODO: Bullet burst animation here
			GameObjectManager::GetInstance().DestroyGameObject(&m_parent);
		}
	}
	break;
	case EventType::REFLECT:
	{
		ReflectEvent * rEvent = static_cast<ReflectEvent*>(aEvent);

		if (!m_body->Tags().HasTag("stationary")) {
			Contact contact = rEvent->GetContact();
			Vector3D newEndPos = PhysicsManager::GetInstance().ReflectShapeOffOtherShape(
				*static_cast<PhysicsComponent*>(contact.LHS_GO()->Get(COMPONENT_TYPE::PHYSICS)),
				*static_cast<PhysicsComponent*>(contact.RHS_GO()->Get(COMPONENT_TYPE::PHYSICS)),
				contact.Collision()
			);
			SetVelocityDirection(newEndPos - contact.Collision().pointOfImpact);
			SetPosition(newEndPos);
		}
	}
	break;
	case EventType::PUSH_FROM_BODY:
	{
		PushFromBodyEvent * rEvent = static_cast<PushFromBodyEvent*>(aEvent);

		if (!m_body->Tags().HasTag("stationary")) {
			Contact contact = rEvent->GetContact();
			Vector3D pushDirection = PhysicsManager::GetInstance().PushShapeOutOfOtherShape(
				*static_cast<PhysicsComponent*>(contact.LHS_GO()->Get(COMPONENT_TYPE::PHYSICS)),
				*static_cast<PhysicsComponent*>(contact.RHS_GO()->Get(COMPONENT_TYPE::PHYSICS)),
				contact.Collision()
			);
			SetPosition(m_position + pushDirection);
		}
	}
	break;
	}
}

void PhysicsComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "Physics components require Transform components." << std::endl;
	m_tComp->SetPosition(m_position);
}

#pragma region Methods

float PhysicsComponent::MaxSpeed() const
{
	return m_maxSpeed;
}

void PhysicsComponent::SetMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

void PhysicsComponent::AddForce(Vector3D force)
{
	m_force += force;
}

Vector3D PhysicsComponent::GetVelocity() const
{
	return m_velocity;
}

void PhysicsComponent::SetVelocity(Vector3D vel)
{
	m_velocity = vel;
}

void PhysicsComponent::SetVelocityDirection(Vector3D dir)
{
	if (!FloatEquals(dir.SquareLength(), 1.f))	dir.Normalize();
	float speed = m_velocity.Length();
	SetVelocity(dir * speed);
}

void PhysicsComponent::InterpolateVelocity(Vector3D vel, float weight)
{
	m_velocity = m_velocity + ((vel - m_velocity) * weight);
}

void PhysicsComponent::SetPosition(Vector3D position)
{
	m_position = position;
}

void PhysicsComponent::SetPrevPosition(Vector3D position)
{
	m_prevPosition = position;
}

// time is assumed to be 0.f - 1.f
Vector3D PhysicsComponent::GetPositionAtTime(float time) const
{
	return m_prevPosition + ((m_position - m_prevPosition) * (time / 1.f));
}

bool PhysicsComponent::IsStatic() const
{
	return m_static;
}

#pragma endregion