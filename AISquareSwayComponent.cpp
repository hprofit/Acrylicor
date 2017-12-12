#include "AISquareSwayComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <iostream>

void AISquareSwayComponent::_HandleDirectionChange()
{
	switch (m_currentDirection) {
	case FORWARD:
	{
		if (m_currentDistanceTravelled >= m_verticalDistance) {
			m_currentDirection = m_previousDirection == RIGHT ? LEFT : RIGHT;
			m_currentDistanceTravelled = 0.f;
		}
	}
	break;

	case LEFT:
	case RIGHT:
	{
		if (m_currentDistanceTravelled >= m_horizontalDistance) {
			m_previousDirection = m_currentDirection;
			m_currentDirection = FORWARD;
			m_currentDistanceTravelled = 0.f;
		}
	}
	break;
	}
}

AISquareSwayComponent::AISquareSwayComponent(GameObject & parent, float speed, float verticalDistance, float horizontalDistance) :
	AIBaseComponent(COMPONENT_TYPE::AI_SQUARE_SWAY, parent),
	m_currentDirection(FORWARD), 
	m_previousDirection(LEFT),
	m_speed(speed), 
	m_verticalDistance(verticalDistance),
	m_horizontalDistance(horizontalDistance),
	m_currentDistanceTravelled(0.f)
{}

AISquareSwayComponent::AISquareSwayComponent(const AISquareSwayComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_RUSH, rhs, parent),
	m_currentDirection(rhs.m_currentDirection), 
	m_previousDirection(rhs.m_previousDirection),
	m_speed(rhs.m_speed), 
	m_verticalDistance(rhs.m_verticalDistance),
	m_horizontalDistance(rhs.m_horizontalDistance),
	m_currentDistanceTravelled(rhs.m_currentDistanceTravelled)
{}

AISquareSwayComponent::~AISquareSwayComponent() {}

void AISquareSwayComponent::Update(double deltaTime)
{
	if (m_active) {
		m_currentDistanceTravelled += m_pComp->GetDistanceTravelledLastFrame();
		_HandleDirectionChange();

		switch (m_currentDirection) {
		case FORWARD:
			m_pComp->InterpolateVelocity(m_tComp->Forward() * m_speed, .5f);
			break;
		case LEFT:
			m_pComp->InterpolateVelocity(m_tComp->Right() * -m_speed, .5f);
			break;
		case RIGHT:
			m_pComp->InterpolateVelocity(m_tComp->Right() * m_speed, .5f);
			break;
		}
	}
}

AISquareSwayComponent * AISquareSwayComponent::Clone(GameObject & parent)
{
	AISquareSwayComponent* comp = new AISquareSwayComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AISquareSwayComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new AISquareSwayComponent(gObject, 
		AcryJson::ParseFloat(j, "aiSquareSway", "speed"),
		AcryJson::ParseFloat(j, "aiSquareSway", "verticalDistance"),
		AcryJson::ParseFloat(j, "aiSquareSway", "horizontalDistance")
	);
}

void AISquareSwayComponent::Override(nlohmann::json j)
{
	m_speed = AcryJson::ValueExists(j, "aiSquareSway", "speed") ? AcryJson::ParseInt(j, "aiSquareSway", "speed") : m_speed;
	m_verticalDistance = AcryJson::ValueExists(j, "aiSquareSway", "verticalDistance") ? AcryJson::ParseInt(j, "aiSquareSway", "verticalDistance") : m_verticalDistance;
	m_horizontalDistance = AcryJson::ValueExists(j, "aiSquareSway", "horizontalDistance") ? AcryJson::ParseInt(j, "aiSquareSway", "horizontalDistance") : m_horizontalDistance;
}

void AISquareSwayComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AISeek components require Transform components." << std::endl;
	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!m_pComp)
		std::cout << "AISeek components require PHysics components." << std::endl;
}
