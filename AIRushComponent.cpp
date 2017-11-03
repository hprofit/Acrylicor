#include "AIRushComponent.h"
#include "JsonReader.h"

// Don't like TODO: Fim_currX
#include "GameObject.h"
#include "TransformComponent.h"

AIRushComponent::AIRushComponent(GameObject & parent, unsigned short moveType, float speed) :
	Component(parent, CT_AI_RUSH),
	m_moveType(moveType), m_speed(speed)
{}

AIRushComponent::AIRushComponent(const AIRushComponent & rhs, GameObject & parent) :
	Component(parent, CT_AI_RUSH),
	m_moveType(rhs.m_moveType), m_speed(rhs.m_speed)
{}

AIRushComponent::~AIRushComponent()
{}

void AIRushComponent::Update(double deltaTime)
{
	TransformComponent* tComp = static_cast<TransformComponent*>(m_parent.Get(CT_TRANSFORM));
	if (!tComp)
		return;

	tComp->Move(tComp->Forward() * deltaTime * m_speed);
}

AIRushComponent * AIRushComponent::Clone(GameObject & parent)
{
	return new AIRushComponent(*this, parent);
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
