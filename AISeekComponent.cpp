#include "AISeekComponent.h"
#include "JsonReader.h"

#include "GameObjectManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector3D.h"
#include "GODestroyedEvent.h"
#include "TargetFoundEvent.h"
#include "Math3D.h"

#include <iostream>
#include <algorithm>

void AISeekComponent::_SeekTarget(double deltaTime)
{
	if (m_target && m_target->IsActive()) {
		Vector3D distanceBetween = m_targetTComp->GetPosition() - m_tComp->GetPosition();
		Vector3D forward = m_tComp->Forward();
		Vector3D left = m_tComp->Right() * -1;

		float numerator = Vector3D::Dot(forward, distanceBetween);
		float denominator = distanceBetween.Length();
		float angle = acosf(numerator / denominator); // (v dot d) / sqrt(square|v|*square|d|) = (v dot d) / (|v|*|d|), thus, reduces the amount of sqrt calls
		
		float direction = Vector3D::Dot(left, distanceBetween); // positive - left, negative - right
		direction = direction / fabsf(direction); // -1 <-> 1

		float rotAmt = std::min(PI_4, fabsf(angle));
		float rotSpd = ((rotAmt / PI_4) * m_maxTurnSpeed);

		float amount = rotSpd * (float)deltaTime * direction;
		m_tComp->RotateZ(amount);
	}
}

AISeekComponent::AISeekComponent(GameObject & parent, float maxTurnSpeed, float speed) :
	AIBaseComponent(COMPONENT_TYPE::AI_SEEK, parent),
	m_maxTurnSpeed(maxTurnSpeed), m_speed(speed)
{}

AISeekComponent::AISeekComponent(const AISeekComponent & rhs, GameObject & parent) : 
	AIBaseComponent(COMPONENT_TYPE::AI_SEEK, rhs, parent),
	m_maxTurnSpeed(rhs.m_maxTurnSpeed), m_speed(rhs.m_speed)
{}

AISeekComponent::~AISeekComponent(){}

void AISeekComponent::Update(double deltaTime)
{
	if (m_active && m_target && !m_target->IsDead())
		_SeekTarget(deltaTime);
}

AISeekComponent * AISeekComponent::Clone(GameObject & parent)
{
	AISeekComponent* comp = new AISeekComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AISeekComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	AISeekComponent* comp = new AISeekComponent(gObject, 
		AcryJson::ParseFloat(j, "aiSeek", "turnSpeed"),
		AcryJson::ParseFloat(j, "aiSeek", "speed")
	);
	comp->_ParseEvents(j, "aiSeek");
	return comp;
}

void AISeekComponent::Override(nlohmann::json j)
{
	m_maxTurnSpeed = AcryJson::ValueExists(j, "aiSeek", "turnSpeed") ? AcryJson::ParseFloat(j, "aiSeek", "turnSpeed") : m_maxTurnSpeed;
	m_speed = AcryJson::ValueExists(j, "aiSeek", "speed") ? AcryJson::ParseFloat(j, "aiSeek", "speed") : m_speed;
}

void AISeekComponent::HandleEvent(AcryEvent * aEvent)
{
	if (m_active) {
		switch (aEvent->Type()) {
		case EventType::GO_DESTROYED:
		{
			GODestroyedEvent * godEvent = static_cast<GODestroyedEvent*>(aEvent);
			if (godEvent->GO() == m_target)
				m_target = nullptr;
		}
		break;
		case EventType::TARGET_FOUND:
		{
			TargetFoundEvent * tfEvent = static_cast<TargetFoundEvent*>(aEvent);
			m_target = tfEvent->GetTarget();
			m_targetTComp = static_cast<TransformComponent*>(m_target->Get(COMPONENT_TYPE::TRANSFORM));
		}
		break;
		}
	}
}

void AISeekComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AISeek components require Transform components." << std::endl;
}
