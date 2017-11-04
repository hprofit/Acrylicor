#include "PhysicsComponent.h"
#include "PhysicsManager.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "TransformComponent.h"

PhysicsComponent::PhysicsComponent(GameObject& parent) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(Vector3D()), m_acceleration(Vector3D()),
	m_position(Vector3D()), m_prevPosition(Vector3D()),
	m_force(Vector3D()),
	m_mass(0.f), m_InvMass(0.f),
	m_body(nullptr)
{ }

PhysicsComponent::PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(velocity), m_acceleration(Vector3D()),
	m_position(position), m_prevPosition(position),
	m_force(Vector3D()),
	m_mass(0.f), m_InvMass(0.f),
	m_body(nullptr)
{ }

PhysicsComponent::PhysicsComponent(GameObject& parent, Vector3D position, Vector3D velocity, Vector3D acceleration) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(velocity), m_acceleration(acceleration),
	m_position(position), m_prevPosition(position),
	m_force(Vector3D()),
	m_mass(0.f), m_InvMass(0.f),
	m_body(nullptr)
{ }

PhysicsComponent::PhysicsComponent(GameObject & parent, Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float invMass) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(velocity), m_acceleration(Vector3D()),
	m_position(position), m_prevPosition(position),
	m_force(Vector3D()),
	m_mass(mass), m_InvMass(invMass),
	m_body(nullptr)
{
}

PhysicsComponent::PhysicsComponent(const PhysicsComponent& rhs, GameObject & parent) :
	Component(parent, CT_PHYSICS, true),
	m_velocity(rhs.m_velocity), m_acceleration(rhs.m_acceleration),
	m_position(rhs.m_position), m_prevPosition(rhs.m_prevPosition),
	m_force(rhs.m_force),
	m_mass(rhs.m_mass), m_InvMass(rhs.m_InvMass),
	m_body(new PhysicsBody(*rhs.m_body))
{
}

PhysicsComponent::~PhysicsComponent()
{
	PhysicsManager::GetInstance().RemoveComponent(this);
}

void PhysicsComponent::Update(double deltaTime)
{
	Update(deltaTime, 0.f);
}

void PhysicsComponent::Update(double deltaTime, float gravity)
{
	m_prevPosition = m_position;

	m_force -= Vector3D(1.f, 1.f, 1.f) * gravity;

	m_acceleration = m_force * m_InvMass;

	m_velocity += m_acceleration * deltaTime;

	m_position += m_velocity * deltaTime;

	m_force = Vector3D();

	TransformComponent * tComp = static_cast<TransformComponent*>(m_parent.Get(CT_TRANSFORM));
	if (tComp) {
		tComp->SetPosition(m_position);
	}
}

PhysicsComponent * PhysicsComponent::Clone(GameObject & parent)
{
	PhysicsComponent* pComp = new PhysicsComponent(*this, parent);
	pComp->RegisterWithManager();
	return pComp;
}

Component * PhysicsComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	Vector3D position = AcryJson::ParseVector3D(j, "physics", "position");
	Vector3D velocity = AcryJson::ParseVector3D(j, "physics", "velocity");
	Vector3D acceleration = AcryJson::ParseVector3D(j, "physics", "acceleration");
	float mass = AcryJson::ParseFloat(j, "physics", "mass");
	float invMass = mass != 0.f ? 1.f / mass : 0.f;

	PhysicsBody * pBody = nullptr;
	String bodyTypeString = AcryJson::ParseString(j, "physics", "body", "type");
	if (bodyTypeString.compare("circle") == 0)
		pBody = new Circle(AcryJson::ParseFloat(j, "physics", "body", "radius"));
	else if (bodyTypeString.compare("aabb") == 0)
		pBody = new AABB(
			AcryJson::ParseFloat(j, "physics", "body", "width"), 
			AcryJson::ParseFloat(j, "physics", "body", "height")
		);

	PhysicsComponent * pComp = new PhysicsComponent(gObject, position, velocity, acceleration, mass, invMass);
	pComp->m_body = pBody;
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

	PhysicsBody * pBody = nullptr;
	String bodyTypeString = AcryJson::ParseString(j, "physics", "body", "type");
	if (bodyTypeString.compare("circle") == 0)
		pBody = new Circle(AcryJson::ParseFloat(j, "physics", "body", "radius"));
	else if (bodyTypeString.compare("aabb") == 0)
		pBody = new AABB(
			AcryJson::ParseFloat(j, "physics", "body", "width"),
			AcryJson::ParseFloat(j, "physics", "body", "height")
		);

	if (pBody)
		m_body = pBody;
}

void PhysicsComponent::RegisterWithManager()
{
	PhysicsManager::GetInstance().AddComponent(this);
}

void PhysicsComponent::AddForce(Vector3D force)
{
	m_force += force;
}
