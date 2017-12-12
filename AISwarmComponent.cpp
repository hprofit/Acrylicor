#include "AISwarmComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "GODestroyedEvent.h"
#include "TargetFoundEvent.h"
#include <iostream>

void AISwarmComponent::_CalculateSwarmMovement(double deltaTime)
{
	Vector3D down = Vector3D(0, -1, 0);
	Vector3D forward = m_tComp->Forward();
	Vector3D left = m_tComp->Right() * -1;
	Vector3D distanceBetween = Vector3D();

	if (m_neighbors.size() != 0) {
		Vector3D pos = m_tComp->GetPosition();
		Vector3D cohesion = Vector3D();
		Vector3D separation = Vector3D();
		Vector3D alignment = Vector3D();
		Vector3D seek = m_targetTComp ? 
			Vector3D::Normalize(m_targetTComp->GetPosition() - pos) : 
			Vector3D();
		

		std::for_each(m_neighbors.begin(), m_neighbors.end(), [pos, &cohesion, &separation, &alignment](TransformComponent* tComp) {
			cohesion += tComp->GetPosition();
			separation += Vector3D::Normalize(pos - tComp->GetPosition());
			alignment += tComp->Forward();
		});
		cohesion = Vector3D::Normalize(((1.f / float(m_neighbors.size())) * cohesion) - pos);
		separation.Normalize();
		alignment.Normalize();


		Vector3D swarmForce = Vector3D::Normalize(
			(cohesion * m_cohWeight) +
			(separation * m_sepWeight) +
			(alignment * m_aliWeight) +
			(seek * m_seekWeight) +
			(down * 1.25f));

		distanceBetween = swarmForce - forward;
	}
	else {
		Vector3D seek = m_targetTComp ?
			Vector3D::Normalize(m_targetTComp->GetPosition() - m_tComp->GetPosition()) :
			Vector3D();

		Vector3D noNeighborForce = Vector3D::Normalize(
			(seek * -m_seekWeight) +
			(down)
		);
		distanceBetween = noNeighborForce - forward;
	}
	
	float numerator = Vector3D::Dot(forward, distanceBetween);
	float denominator = distanceBetween.Length();
	float angle = acosf(numerator / denominator); // (v dot d) / sqrt(square|v|*square|d|) = (v dot d) / (|v|*|d|), thus, reduces the amount of sqrt calls

	float direction = Vector3D::Dot(left, distanceBetween); // positive - left, negative - right
	direction = direction != 0.f ? direction / fabsf(direction) : 1.f; // -1 <-> 1

	float rotAmt = std::min(PI_4, fabsf(angle));
	float rotSpd = ((rotAmt / PI_4) * m_maxTurnSpeed);

	float amount = rotSpd * (float)deltaTime * direction;
	m_tComp->RotateZ(amount);
}

void AISwarmComponent::_FindNeighbors()
{
	m_neighbors.erase(m_neighbors.begin(), m_neighbors.begin() + m_neighbors.size());
	std::vector<GameObject*> objects = GameObjectManager::GetInstance().GetObjectsWithTag("swarm");

	if (objects.size() != 0) {
		objects.erase(std::remove_if(objects.begin(), objects.end(),
			[this](GameObject* go) {
				if (go == &m_parent) 
					return true;
				TransformComponent* tComp = static_cast<TransformComponent*>(go->Get(COMPONENT_TYPE::TRANSFORM));
				float distance = Vector3D::SquareDistance(tComp->GetPosition(), m_tComp->GetPosition());
				return distance > m_viewDistanceSq;
			}
		),
			objects.end()
		);
		std::for_each(objects.begin(), objects.end(), [this](GameObject* go) {
			m_neighbors.push_back(static_cast<TransformComponent*>(go->Get(COMPONENT_TYPE::TRANSFORM)));
		});
	}
}

AISwarmComponent::AISwarmComponent(GameObject & parent, float viewDistance, float maxTurnSpeed, float speed, float cohWeight, float sepWeight, float aliWeight, float seekWeight) :
	AIBaseComponent(COMPONENT_TYPE::AI_SWARM, parent),
	m_speed(speed),
	m_maxTurnSpeed(maxTurnSpeed),
	m_viewDistance(viewDistance),
	m_viewDistanceSq(viewDistance * viewDistance),
	m_cohWeight(cohWeight),
	m_sepWeight(sepWeight),
	m_aliWeight(aliWeight),
	m_seekWeight(seekWeight)
{}

AISwarmComponent::AISwarmComponent(const AISwarmComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_SWARM, rhs, parent),
	m_speed(rhs.m_speed),
	m_maxTurnSpeed(rhs.m_maxTurnSpeed),
	m_viewDistance(rhs.m_viewDistance),
	m_viewDistanceSq(rhs.m_viewDistanceSq),
	m_cohWeight(rhs.m_cohWeight),
	m_sepWeight(rhs.m_sepWeight),
	m_aliWeight(rhs.m_aliWeight),
	m_seekWeight(rhs.m_seekWeight)
{}

AISwarmComponent::~AISwarmComponent() {}

void AISwarmComponent::Update(double deltaTime)
{
	if (m_active) {
		_FindNeighbors();
		_CalculateSwarmMovement(deltaTime);
	}
}

AISwarmComponent * AISwarmComponent::Clone(GameObject & parent)
{
	AISwarmComponent* comp = new AISwarmComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AISwarmComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	AISwarmComponent* comp = new AISwarmComponent(gObject,
		AcryJson::ParseFloat(j, "aiSwarm", "viewDistance"),
		AcryJson::ParseFloat(j, "aiSwarm", "turnSpeed"),
		AcryJson::ParseFloat(j, "aiSwarm", "speed"),
		AcryJson::ParseFloat(j, "aiSwarm", "cohesion"),
		AcryJson::ParseFloat(j, "aiSwarm", "separation"),
		AcryJson::ParseFloat(j, "aiSwarm", "alignment"),
		AcryJson::ParseFloat(j, "aiSwarm", "seek")
	);
	comp->_ParseEvents(j, "aiSwarm");
	return comp;
}

void AISwarmComponent::Override(nlohmann::json j)
{
	m_viewDistance = AcryJson::ValueExists(j, "aiSwarm", "viewDistance") ? AcryJson::ParseFloat(j, "aiSwarm", "viewDistance") : m_viewDistance;
	m_viewDistanceSq = m_viewDistance * m_viewDistance;
	m_maxTurnSpeed = AcryJson::ValueExists(j, "aiSwarm", "turnSpeed") ? AcryJson::ParseFloat(j, "aiSwarm", "turnSpeed") : m_maxTurnSpeed;
	m_speed = AcryJson::ValueExists(j, "aiSwarm", "speed") ? AcryJson::ParseFloat(j, "aiSwarm", "speed") : m_speed;

	m_cohWeight = AcryJson::ValueExists(j, "aiSwarm", "cohesion") ? AcryJson::ParseFloat(j, "aiSwarm", "cohesion") : m_cohWeight;
	m_sepWeight = AcryJson::ValueExists(j, "aiSwarm", "separation") ? AcryJson::ParseFloat(j, "aiSwarm", "separation") : m_sepWeight;
	m_aliWeight = AcryJson::ValueExists(j, "aiSwarm", "alignment") ? AcryJson::ParseFloat(j, "aiSwarm", "alignment") : m_aliWeight;
	m_seekWeight = AcryJson::ValueExists(j, "aiSwarm", "seek") ? AcryJson::ParseFloat(j, "aiSwarm", "seek") : m_seekWeight;
}

void AISwarmComponent::HandleEvent(AcryEvent * aEvent)
{
	if (m_active) {
		switch (aEvent->Type()) {
		case EventType::GO_DESTROYED:
		{
			GODestroyedEvent * godEvent = static_cast<GODestroyedEvent*>(aEvent);
			if (godEvent->GO() == m_target) {
				m_target = nullptr;
				m_targetTComp = nullptr;
			}
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

void AISwarmComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AISwarm components require Transform components." << std::endl;

	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	if (!m_pComp)
		std::cout << "AISwarm components require Physics components." << std::endl;
}
