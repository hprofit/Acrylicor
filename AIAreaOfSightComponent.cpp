#include "AIAreaOfSightComponent.h"
#include "JsonReader.h"

#include "GameObjectManager.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"

#include "TargetFoundEvent.h"

#include <iostream>
#include <algorithm>

void AIAreaOfSightComponent::_FindNewTarget()
{
	std::vector<GameObject*> objects = GameObjectManager::GetInstance().GetObjectsWithTag(m_tagToFind);

	if (objects.size() != 0) {
		unsigned int i = 1;
		Vector3D pos = m_tComp->GetPosition();
		TransformComponent* tComp = static_cast<TransformComponent*>(objects[0]->Get(COMPONENT_TYPE::TRANSFORM));
		float closestDistance = Vector3D::SquareDistance(tComp->GetPosition(), pos);

		GameObject* target = objects[0];

		for (i = 1; i < objects.size(); ++i) {
			tComp = static_cast<TransformComponent*>(objects[i]->Get(COMPONENT_TYPE::TRANSFORM));
			float distance = Vector3D::SquareDistance(tComp->GetPosition(), pos);
			if (distance < closestDistance) {
				target = objects[i];
				closestDistance = distance;
			}
		}

		if (closestDistance < m_searchRadiusSq) {
			m_parent.HandleEvent(new TargetFoundEvent(target));
		}
	}
}

AIAreaOfSightComponent::AIAreaOfSightComponent(GameObject & parent, String tagToFind, float searchRadius) :
	Component(parent, COMPONENT_TYPE::AI_AREA_OF_SIGHT),
	m_tagToFind(tagToFind), m_searchRadius(searchRadius), m_searchRadiusSq(searchRadius * searchRadius), m_foundTarget(false)
{}

AIAreaOfSightComponent::AIAreaOfSightComponent(const AIAreaOfSightComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::AI_AREA_OF_SIGHT),
	m_tagToFind(rhs.m_tagToFind),
	m_searchRadius(rhs.m_searchRadius),
	m_searchRadiusSq(rhs.m_searchRadiusSq),
	m_foundTarget(false)
{}

AIAreaOfSightComponent::~AIAreaOfSightComponent() {}

void AIAreaOfSightComponent::Update(double deltaTime)
{
	_FindNewTarget();
}

AIAreaOfSightComponent * AIAreaOfSightComponent::Clone(GameObject & parent)
{
	AIAreaOfSightComponent* comp = new AIAreaOfSightComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * AIAreaOfSightComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	AIAreaOfSightComponent* comp = new AIAreaOfSightComponent(gObject,
		AcryJson::ParseString(j, "aiAreaOfSight", "targetTag"),
		AcryJson::ParseFloat(j, "aiAreaOfSight", "radius")
	);
	comp->_ParseEvents(j, "aiAreaOfSight");
	return comp;
}

void AIAreaOfSightComponent::Override(nlohmann::json j)
{
	m_tagToFind = AcryJson::ValueExists(j, "aiAreaOfSight", "targetTag") ? AcryJson::ParseString(j, "aiAreaOfSight", "targetTag") : m_tagToFind;
	if (AcryJson::ValueExists(j, "aiAreaOfSight", "radius")) {
		m_searchRadiusSq = AcryJson::ParseFloat(j, "aiAreaOfSight", "radius");
		m_searchRadiusSq *= m_searchRadiusSq;
	}
}

void AIAreaOfSightComponent::HandleEvent(AcryEvent * aEvent)
{}

void AIAreaOfSightComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AIAreaOfSight components require Transform components." << std::endl;
}
