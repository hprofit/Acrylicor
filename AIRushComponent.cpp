#include "AIRushComponent.h"
#include "JsonReader.h"

// Don't like TODO: fix
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"

AIRushComponent::AIRushComponent(GameObject & parent, unsigned short moveType, float speed) :
	Component(parent, COMPONENT_TYPE::AI_RUSH),
	m_moveType(moveType), m_speed(speed)
{}

AIRushComponent::AIRushComponent(const AIRushComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::AI_RUSH),
	m_moveType(rhs.m_moveType), m_speed(rhs.m_speed)
{}

AIRushComponent::~AIRushComponent()
{}

void AIRushComponent::Update(double deltaTime)
{
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent* pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!tComp || !pComp)
		return;

	pComp->InterpolateVelocity(tComp->Forward() * m_speed, .5f);
}

AIRushComponent * AIRushComponent::Clone(GameObject & parent)
{
	AIRushComponent* comp = new AIRushComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * AIRushComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	String moveTypeString = AcryJson::ParseString(j, "aiRush", "direction");
	unsigned short moveType = moveTypeString.compare("forward") == 0 ? FORWARD : FORWARD;
	float speed = AcryJson::ParseFloat(j, "aiRush", "speed");
	return new AIRushComponent(gObject, moveType, speed);
}

void AIRushComponent::Override(nlohmann::json j)
{
	if (AcryJson::ValueExists(j, "aiRush", "direction")) {
		String moveTypeString = AcryJson::ParseString(j, "aiRush", "direction");
		m_moveType = moveTypeString.compare("forward") == 0 ? FORWARD : FORWARD;
	}
	m_speed = AcryJson::ValueExists(j, "aiRush", "speed") ? AcryJson::ParseInt(j, "aiRush", "speed") : m_speed;
}
