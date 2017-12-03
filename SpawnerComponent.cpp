#include "SpawnerComponent.h"
#include "JsonReader.h"
#include "AcryEvent.h"
#include "GameObjectManager.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"

SpawnerComponent::SpawnerComponent(GameObject& parent, String objectType) :
	Component(parent, COMPONENT_TYPE::SPAWNER),
	m_objectType(objectType){}

SpawnerComponent::SpawnerComponent(const SpawnerComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::SPAWNER),
	m_objectType(rhs.m_objectType) {}

SpawnerComponent::~SpawnerComponent() {}

void SpawnerComponent::Update(double deltaTime)
{}

SpawnerComponent * SpawnerComponent::Clone(GameObject & parent)
{
	SpawnerComponent * comp = new SpawnerComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * SpawnerComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	SpawnerComponent* comp = new SpawnerComponent(gObject,
		AcryJson::ParseString(j, "spawner", "type")
	);
	comp->_ParseEvents(j, "spawner");

	return comp;
}

void SpawnerComponent::Override(nlohmann::json j)
{
	m_objectType = AcryJson::ValueExists(j, "spawner", "type") ? AcryJson::ParseString(j, "spawner", "type") : m_objectType;
	_ParseEvents(j, "spawner");
}

void SpawnerComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::RESPAWN:
	{
		GameObject* gObject = GameObjectManager::GetInstance().SpawnGameObject(m_objectType);

		TransformComponent* sTComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
		PhysicsComponent* goPComp = static_cast<PhysicsComponent*>(gObject->Get(COMPONENT_TYPE::PHYSICS));

		if (sTComp && goPComp) {
			goPComp->SetPosition(sTComp->GetPosition());
			goPComp->SetPrevPosition(sTComp->GetPosition());
		}
		else {
			TransformComponent* goTComp = static_cast<TransformComponent*>(gObject->Get(COMPONENT_TYPE::TRANSFORM));
			if (sTComp && goTComp)
				goTComp->SetPosition(sTComp->GetPosition());
		}
	}
	break;
	}
}