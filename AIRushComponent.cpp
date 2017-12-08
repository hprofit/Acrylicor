#include "AIRushComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <iostream>

AIRushComponent::AIRushComponent(GameObject & parent, unsigned short moveType, float speed) :
	AIBaseComponent(COMPONENT_TYPE::AI_RUSH, parent),
	m_moveType(moveType), m_speed(speed)
{}

AIRushComponent::AIRushComponent(const AIRushComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_RUSH, rhs, parent),
	m_moveType(rhs.m_moveType), m_speed(rhs.m_speed)
{}

AIRushComponent::~AIRushComponent(){}

void AIRushComponent::Update(double deltaTime)
{
	switch (m_moveType) {
	case FORWARD:
		m_pComp->InterpolateVelocity(m_tComp->Forward() * m_speed, .5f);
		break;
	case LEFT:
		m_pComp->InterpolateVelocity(m_tComp->Right() * -m_speed, .5f);
		break;
	case RIGHT:
		m_pComp->InterpolateVelocity(m_tComp->Right() * m_speed, .5f);
		break;
	case BACKWARD:
		m_pComp->InterpolateVelocity(m_tComp->Forward() * -m_speed, .5f);
		break;
	}
}

AIRushComponent * AIRushComponent::Clone(GameObject & parent)
{
	AIRushComponent* comp = new AIRushComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AIRushComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	String moveTypeString = AcryJson::ParseString(j, "aiRush", "direction");
	unsigned short moveType = 0;
	
	if (moveTypeString == "left")			moveType = 1;
	else if (moveTypeString == "right")		moveType = 2;
	else if (moveTypeString == "backward")	moveType = 3;

	float speed = AcryJson::ParseFloat(j, "aiRush", "speed");
	return new AIRushComponent(gObject, moveType, speed);
}

void AIRushComponent::Override(nlohmann::json j)
{
	if (AcryJson::ValueExists(j, "aiRush", "direction")) {
		String moveTypeString = AcryJson::ParseString(j, "aiRush", "direction");
		if (moveTypeString == "forward")		m_moveType = 0;
		else if (moveTypeString == "left")		m_moveType = 1;
		else if (moveTypeString == "right")		m_moveType = 2;
		else if (moveTypeString == "backward")	m_moveType = 3;
	}

	m_speed = AcryJson::ValueExists(j, "aiRush", "speed") ? AcryJson::ParseInt(j, "aiRush", "speed") : m_speed;
}

void AIRushComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AISeek components require Transform components." << std::endl;
	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!m_pComp)
		std::cout << "AISeek components require PHysics components." << std::endl;
}
