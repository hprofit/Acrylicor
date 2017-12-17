#include "AISpawnOnDeathComponent.h"
#include "JsonReader.h"
#include "AddScoreEvent.h"
#include "GameObject.h"
#include "SpawnerComponent.h"
#include <iostream>

AISpawnOnDeathComponent::AISpawnOnDeathComponent(GameObject & parent, int amount) :
	AIBaseComponent(COMPONENT_TYPE::AI_SPAWN_ON_DEATH, parent),
	m_amount(amount)
{}

AISpawnOnDeathComponent::AISpawnOnDeathComponent(const AISpawnOnDeathComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_SPAWN_ON_DEATH, rhs, parent),
	m_amount(rhs.m_amount)
{}

AISpawnOnDeathComponent::~AISpawnOnDeathComponent() {}

void AISpawnOnDeathComponent::Update(double deltaTime){}

AISpawnOnDeathComponent * AISpawnOnDeathComponent::Clone(GameObject & parent)
{
	AISpawnOnDeathComponent* comp = new AISpawnOnDeathComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AISpawnOnDeathComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	AISpawnOnDeathComponent * comp = new AISpawnOnDeathComponent(gObject, AcryJson::ParseInt(j, "aiSpawnOnDeath", "amount"));
	comp->_ParseEvents(j, "aiSpawnOnDeath");
	return comp;
}

void AISpawnOnDeathComponent::Override(nlohmann::json j)
{
	m_amount = AcryJson::ValueExists(j, "aiSpawnOnDeath", "amount") ? AcryJson::ParseInt(j, "aiSpawnOnDeath", "amount") : m_amount;
}

void AISpawnOnDeathComponent::HandleEvent(AcryEvent * aEvent)
{
	if (m_active) {
		switch (aEvent->Type()) {
		case EventType::ADD_SCORE:
		{
			AddScoreEvent* asEvent = static_cast<AddScoreEvent*>(aEvent);
			if (asEvent->GO()->GetId() == m_parent.GetId())
				m_sComp->SpawnMultiple(m_amount);
		}
		break;
		}
	}
}

void AISpawnOnDeathComponent::LateInitialize()
{
	m_sComp = static_cast<SpawnerComponent*>(m_parent.Get(COMPONENT_TYPE::SPAWNER));
	if (!m_sComp)
		std::cout << "AISpawnOnDeath components require Spawner components." << std::endl;
}
