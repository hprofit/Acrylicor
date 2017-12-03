#include "AISwayComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <math.h>

AISwayComponent::AISwayComponent(GameObject & parent, float swayAmount) :
	Component(parent, COMPONENT_TYPE::AI_SWAY),
	m_swayAmount(swayAmount),
	m_currX(-1.f), m_direction(1.f)
{}

AISwayComponent::AISwayComponent(const AISwayComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::AI_SWAY),
	m_swayAmount(rhs.m_swayAmount),
	m_currX(-1.f), m_direction(1.f)
{}

AISwayComponent::~AISwayComponent(){}

void AISwayComponent::Update(double deltaTime)
{
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	PhysicsComponent* pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!tComp || !pComp)
		return;

	m_currX += (float)deltaTime * m_direction;
	if (m_currX >= 1.f) {
		m_currX = 1.f;
		m_direction = -1.f;
	}
	else if (m_currX <= -1.f) {
		m_currX = -1.f;
		m_direction = 1.f;
	}

	pComp->InterpolateVelocity(tComp->Right() * asinf(m_currX) * m_swayAmount, .5f);
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
	float swayAmount = AcryJson::ValueExists(j, "aiSway", "amount") ? AcryJson::ParseFloat(j, "aiSway", "amount") : 1.f;
	return new AISwayComponent(gObject, swayAmount);
}

void AISwayComponent::Override(nlohmann::json j)
{
	m_swayAmount = AcryJson::ValueExists(j, "aiSway", "amount") ? AcryJson::ParseFloat(j, "aiSway", "amount") : m_swayAmount;
}
