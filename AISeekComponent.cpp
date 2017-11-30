#include "AISeekComponent.h"
#include "JsonReader.h"

#include "GameObjectManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Vector3D.h"
#include "GODestroyedEvent.h"
#include "Math3D.h"

#include <iostream>
#include <algorithm>

void AISeekComponent::_FindNewTarget()
{
	std::vector<GameObject*> objects = GameObjectManager::GetInstance().GetObjectsWithTag(m_tagToFind);
	
	if (objects.size() != 0) {
		unsigned int i = 1;
		Vector3D pos = m_tComp->GetPosition();
		TransformComponent* tComp = static_cast<TransformComponent*>(objects[0]->Get(COMPONENT_TYPE::TRANSFORM));
		float closestDistance = Vector3D::SquareDistance(tComp->GetPosition(), pos);
		m_target = objects[0];
		m_targetTComp = tComp;

		for (i = 1; i < objects.size(); ++i) {
			tComp = static_cast<TransformComponent*>(objects[i]->Get(COMPONENT_TYPE::TRANSFORM));
			float distance = Vector3D::SquareDistance(tComp->GetPosition(), pos);
			if (distance < closestDistance) {
				m_target = objects[i];
				m_targetTComp = tComp;
				closestDistance = distance;
			}
		}
		
	}
}

void AISeekComponent::_SeekTarget(double deltaTime)
{
	if (m_target && m_target->IsActive()) {
		Vector3D distanceBetween = m_targetTComp->GetPosition() - m_tComp->GetPosition();
		Vector3D homingMissleVelocity = m_pComp->GetVelocity();

		if (FloatEquals(homingMissleVelocity.SquareLength(), 0.f)) homingMissleVelocity = m_tComp->Forward();

		float numerator = Vector3D::Dot(homingMissleVelocity, distanceBetween);
		float denominator = homingMissleVelocity.Length() * distanceBetween.Length();
		float angle = acosf(numerator / denominator); // (v dot d) / sqrt(square|v|*square|d|) = (v dot d) / (|v|*|d|), thus, reduces the amount of sqrt calls
		
		Vector3D vectorLeft = Vector3D(-(homingMissleVelocity.getY()), homingMissleVelocity.getX(), 0.f); // create the rotated velocity vector

		float direction = Vector3D::Dot(vectorLeft, distanceBetween); // positive - left, negative - right
		direction = direction / fabsf(direction); // -1 <-> 1

		float rotAmt = std::min(PI_4, fabsf(angle));
		float rotSpd = ((rotAmt / PI_4) * m_maxTurnSpeed);

		float amount = rotSpd * (float)deltaTime * direction;
		m_tComp->RotateZ(amount);
		float angleZ = m_tComp->GetAngleZ();
		//std::cout << "Angle: " << angleZ << std::endl;
		//std::cout << "Turn amount: " << amount << std::endl;

		m_pComp->InterpolateVelocity(Vector3D(cosf(angleZ), sinf(angleZ), 0.f) * m_speed, 1.f);
	}
}

AISeekComponent::AISeekComponent(GameObject & parent, String tagToFind, float maxTurnSpeed, float speed) :
	Component(parent, COMPONENT_TYPE::AI_SEEK),
	m_tagToFind(tagToFind), m_maxTurnSpeed(maxTurnSpeed), m_speed(speed)
{}

AISeekComponent::AISeekComponent(const AISeekComponent & rhs, GameObject & parent) : 
	Component(parent, COMPONENT_TYPE::AI_SEEK),
	m_tagToFind(rhs.m_tagToFind), m_maxTurnSpeed(rhs.m_maxTurnSpeed), m_speed(rhs.m_speed)
{}

AISeekComponent::~AISeekComponent()
{}

void AISeekComponent::Update(double deltaTime)
{
	if (!m_target || (m_target && m_target->IsDead()))
		_FindNewTarget();
	else
		_SeekTarget(deltaTime);
}

AISeekComponent * AISeekComponent::Clone(GameObject & parent)
{
	AISeekComponent* comp = new AISeekComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * AISeekComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	AISeekComponent* comp = new AISeekComponent(gObject, 
		AcryJson::ParseString(j, "aiSeek", "targetTag"), 
		AcryJson::ParseFloat(j, "aiSeek", "turnSpeed"),
		AcryJson::ParseFloat(j, "aiSeek", "speed")
	);
	comp->_ParseEvents(j, "aiSeek");
	return comp;
}

void AISeekComponent::Override(nlohmann::json j)
{
	m_tagToFind = AcryJson::ValueExists(j, "aiSeek", "targetTag") ? AcryJson::ParseString(j, "aiSeek", "targetTag"): m_tagToFind;
	m_maxTurnSpeed = AcryJson::ValueExists(j, "aiSeek", "turnSpeed") ? AcryJson::ParseFloat(j, "aiSeek", "turnSpeed") : m_maxTurnSpeed;
	m_speed = AcryJson::ValueExists(j, "aiSeek", "speed") ? AcryJson::ParseFloat(j, "aiSeek", "speed") : m_speed;
}

void AISeekComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::GO_DESTROYED:
	{
		GODestroyedEvent * godEvent = static_cast<GODestroyedEvent*>(aEvent);
		if (godEvent->GO()->Tags().HasTag(m_tagToFind))
			m_target = nullptr;
	}
	break;
	}
}

void AISeekComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!m_tComp)
		std::cout << "AISeek components require Transform components." << std::endl;
	if (!m_pComp)
		std::cout << "AISeek components require Physics components." << std::endl;
}
