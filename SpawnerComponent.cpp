#include "SpawnerComponent.h"
#include "JsonReader.h"
#include "AcryEvent.h"
#include "GameObjectManager.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Math3D.h"
#include <iostream>

void SpawnerComponent::_Spawn()
{
	std::cout << "Spawning <" << m_objectType << ">" << std::endl;
	GameObject* gObject = GameObjectManager::GetInstance().SpawnGameObject(m_objectType);

	PhysicsComponent* goPComp = static_cast<PhysicsComponent*>(gObject->Get(COMPONENT_TYPE::PHYSICS));

	if (goPComp) {
		goPComp->SetPosition(m_tComp->GetPosition());
		goPComp->SetPrevPosition(m_tComp->GetPosition());
	}
	else {
		TransformComponent* goTComp = static_cast<TransformComponent*>(gObject->Get(COMPONENT_TYPE::TRANSFORM));
		if (goTComp)
			goTComp->SetPosition(m_tComp->GetPosition());
	}
}

SpawnerComponent::SpawnerComponent(GameObject& parent, String objectType) :
	Component(parent, COMPONENT_TYPE::SPAWNER),
	m_objectType(objectType){}

SpawnerComponent::SpawnerComponent(const SpawnerComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::SPAWNER),
	m_objectType(rhs.m_objectType) {}

SpawnerComponent::~SpawnerComponent() {}

void SpawnerComponent::Update(double deltaTime){}

SpawnerComponent * SpawnerComponent::Clone(GameObject & parent)
{
	SpawnerComponent * comp = new SpawnerComponent(*this, parent);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * SpawnerComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new SpawnerComponent(gObject, AcryJson::ParseString(j, "spawner", "type") );
}

void SpawnerComponent::Override(nlohmann::json j)
{
	m_objectType = AcryJson::ValueExists(j, "spawner", "type") ? AcryJson::ParseString(j, "spawner", "type") : m_objectType;
	_ParseEvents(j, "spawner");
	_SubscribeToEvents(this->m_eventsToSubscribeTo);
}

void SpawnerComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::GAME_OVER:
	{
		GameObjectManager::GetInstance().DestroyGameObject(&m_parent);
	}
	break;
	case EventType::RESPAWN:
	{
		_Spawn();
	}
	break;
	case EventType::SPAWN:
	{
		SpawnMultiple(10);
	}
	break;
	}
}

void SpawnerComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "Spawner components require Transform components." << std::endl;
}

void SpawnerComponent::SpawnMultiple(unsigned int amount)
{
	std::cout << "Spawning x" << amount << " <" << m_objectType << ">" << std::endl;
	std::vector<GameObject*> gos = std::vector<GameObject*>();
	gos.reserve(amount);
	for (unsigned int i = 0; i < amount; ++i)
		gos.push_back(GameObjectManager::GetInstance().SpawnGameObject(m_objectType));

	Vector3D AXIS_Z = Vector3D(0, 0, 1);
	Vector3D pos = m_tComp->GetPosition();
	float max = 10.0;
	float degreeAmt = 360.f / max;
	Matrix4x4 Position = Matrix4x4::Translate(Vector3D(pos.getX(), pos.getY(), 0));
	Matrix4x4 Base = Matrix4x4::Translate(Vector3D(100, 0, 0));
	int i = 0;

	std::for_each(gos.begin(), gos.end(), [&Base, &degreeAmt, &Position, &AXIS_Z, &i](GameObject* go) {
		Matrix4x4 Rot = Matrix4x4::Rotate(degreeAmt * float(i), AXIS_Z);
		Vector3D thisPos = Position * Rot * Base * Vector3D();
		PhysicsComponent* goPComp = static_cast<PhysicsComponent*>(go->Get(COMPONENT_TYPE::PHYSICS));

		if (goPComp) {
			goPComp->SetPosition(thisPos);
			goPComp->SetPrevPosition(thisPos);
		}
		else {
			TransformComponent* goTComp = static_cast<TransformComponent*>(go->Get(COMPONENT_TYPE::TRANSFORM));
			if (goTComp)
				goTComp->SetPosition(thisPos);
		}
		++i;
	});
}
