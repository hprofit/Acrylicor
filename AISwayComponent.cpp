#include "AISwayComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <math.h>
#include <iostream>

AISwayComponent::AISwayComponent(GameObject & parent, float swayAmount, float speed) :
	AIBaseComponent(COMPONENT_TYPE::AI_SWAY, parent),
	m_swayAmount(swayAmount),
	m_currX(-1.f), m_direction(1.f),
	m_speed(speed)
{}

AISwayComponent::AISwayComponent(const AISwayComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_SWAY, rhs, parent),
	m_swayAmount(rhs.m_swayAmount),
	m_currX(-1.f), m_direction(1.f),
	m_speed(rhs.m_speed)
{}

AISwayComponent::~AISwayComponent(){}

void AISwayComponent::Update(double deltaTime)
{
	if (m_active) {
		m_currX += (float)deltaTime * m_direction * m_speed;
		if (m_currX >= 1.f) {
			m_currX = 1.f;
			m_direction = -1.f;
		}
		else if (m_currX <= -1.f) {
			m_currX = -1.f;
			m_direction = 1.f;
		}

		m_pComp->InterpolateVelocity(m_tComp->Right() * asinf(m_currX) * m_swayAmount, .5f);
	}
}

AISwayComponent * AISwayComponent::Clone(GameObject & parent)
{
	AISwayComponent* comp = new AISwayComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AISwayComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new AISwayComponent(gObject, 
		AcryJson::ParseFloat(j, "aiSway", "amount"),
		AcryJson::ParseFloat(j, "aiSway", "speed")
	);
}

void AISwayComponent::Override(nlohmann::json j)
{
	m_swayAmount = AcryJson::ValueExists(j, "aiSway", "amount") ? AcryJson::ParseFloat(j, "aiSway", "amount") : m_swayAmount;
	m_speed = AcryJson::ValueExists(j, "aiSway", "speed") ? AcryJson::ParseFloat(j, "aiSway", "speed") : m_speed;
}

void AISwayComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AISeek components require Transform components." << std::endl;
	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!m_pComp)
		std::cout << "AISeek components require PHysics components." << std::endl;
}