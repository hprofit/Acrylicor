#include "AISwayComponent.h"
#include "JsonReader.h"
//#include <iostream>

// Don't like TODO: Fim_currX
#include "GameObject.h"
#include "TransformComponent.h"

AISwayComponent::AISwayComponent(GameObject & parent, float swayAmount) :
	Component(parent, CT_AI_SWAY),
	m_swayAmount(swayAmount),
	m_currX(-1.f), m_direction(1.f)
{}

AISwayComponent::AISwayComponent(const AISwayComponent & rhs, GameObject & parent) :
	Component(parent, CT_AI_SWAY),
	m_swayAmount(rhs.m_swayAmount),
	m_currX(-1.f), m_direction(1.f)
{}

AISwayComponent::~AISwayComponent(){}

void AISwayComponent::Update(double deltaTime)
{
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(CT_TRANSFORM));
	if (!tComp)
		return;

	m_currX += deltaTime * m_direction;
	if (m_currX >= 1.f) {
		m_currX = 1.f;
		m_direction = -1.f;
	}
	else if (m_currX <= -1.f) {
		m_currX = -1.f;
		m_direction = 1.f;
	}

	tComp->Move(tComp->Right() * asinf(m_currX) * deltaTime * m_swayAmount);
}

AISwayComponent * AISwayComponent::Clone(GameObject & parent)
{
	return new AISwayComponent(*this, parent);
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
