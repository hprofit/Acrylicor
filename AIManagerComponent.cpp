#include "AIManagerComponent.h"
#include "JsonReader.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <unordered_map>
#include <iostream>


void AIManagerComponent::_AcivateAIComponents()
{
	std::for_each(m_aiComponentsToActivate.begin(), m_aiComponentsToActivate.end(), [](AIBaseComponent* comp) {
		comp->Activate();
	});
}

void AIManagerComponent::_DeactivateAIComponents()
{
	std::for_each(m_aiComponentsToDeactivate.begin(), m_aiComponentsToDeactivate.end(), [](AIBaseComponent* comp) {
		comp->Deactivate();
	});
}

AIManagerComponent::AIManagerComponent(GameObject & parent, float range) :
	AIBaseComponent(COMPONENT_TYPE::AI_MANAGER, parent),
	m_range(range),
	m_aiComponentTypesToActivate(std::vector<String>()),
	m_aiComponentTypesToDeactivate(std::vector<String>()),
	m_aiComponentsToActivate(std::vector<AIBaseComponent*>()),
	m_aiComponentsToDeactivate(std::vector<AIBaseComponent*>())
{}

AIManagerComponent::AIManagerComponent(const AIManagerComponent & rhs, GameObject & parent) :
	AIBaseComponent(COMPONENT_TYPE::AI_MANAGER, rhs, parent),
	m_range(rhs.m_range),
	m_aiComponentTypesToActivate(rhs.m_aiComponentTypesToActivate),
	m_aiComponentTypesToDeactivate(rhs.m_aiComponentTypesToDeactivate),
	m_aiComponentsToActivate(rhs.m_aiComponentsToActivate),
	m_aiComponentsToDeactivate(rhs.m_aiComponentsToDeactivate)
{}

AIManagerComponent::~AIManagerComponent() {}

void AIManagerComponent::Update(double deltaTime)
{
	if (m_tComp->GetPosition().getY() <= m_range) {
		_AcivateAIComponents();
		_DeactivateAIComponents();
	}
}

AIManagerComponent * AIManagerComponent::Clone(GameObject & parent)
{
	AIManagerComponent* comp = new AIManagerComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * AIManagerComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	AIManagerComponent* comp = new AIManagerComponent(gObject);
	comp->m_aiComponentTypesToActivate = AcryJson::ParseStringList(j, "aiManager", "components", "activate");
	comp->m_aiComponentTypesToDeactivate = AcryJson::ParseStringList(j, "aiManager", "components", "deactivate");
	return comp;
}

void AIManagerComponent::Override(nlohmann::json j)
{
	m_aiComponentTypesToActivate = AcryJson::ValueExists(j, "aiManager", "components", "activate") ? AcryJson::ParseStringList(j, "aiManager", "components", "activate") : m_aiComponentTypesToActivate;
	m_aiComponentTypesToDeactivate = AcryJson::ValueExists(j, "aiManager", "components", "deactivate") ? AcryJson::ParseStringList(j, "aiManager", "components", "deactivate") : m_aiComponentTypesToDeactivate;
}

void AIManagerComponent::LateInitialize()
{
	std::unordered_map<String, COMPONENT_TYPE> aiTypes = {
		{ "aiAreaOfSight", COMPONENT_TYPE::AI_AREA_OF_SIGHT },
		{ "aiFireFun", COMPONENT_TYPE::AI_FIRE_GUN },
		{ "aiRush", COMPONENT_TYPE::AI_RUSH },
		{ "aiSeek", COMPONENT_TYPE::AI_SEEK },
		{ "aiSpawnOnDeath", COMPONENT_TYPE::AI_SPAWN_ON_DEATH },
		{ "aiSquareSway", COMPONENT_TYPE::AI_SQUARE_SWAY },
		{ "aiSwarm", COMPONENT_TYPE::AI_SWARM },
		{ "aiSway", COMPONENT_TYPE::AI_SWAY }
	};
	std::for_each(m_aiComponentTypesToActivate.begin(), m_aiComponentTypesToActivate.end(), [this, &aiTypes](String aiCompType) {
		AIBaseComponent* comp = static_cast<AIBaseComponent*>(m_parent.Get(aiTypes[aiCompType]));
		comp->Deactivate();
		m_aiComponentsToActivate.push_back(comp);
	});
	m_aiComponentTypesToActivate.clear();
	std::for_each(m_aiComponentTypesToDeactivate.begin(), m_aiComponentTypesToDeactivate.end(), [this, &aiTypes](String aiCompType) {
		m_aiComponentsToDeactivate.push_back(static_cast<AIBaseComponent*>(m_parent.Get(aiTypes[aiCompType])));
	});
	m_aiComponentTypesToDeactivate.clear();

	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "AISeek components require Transform components." << std::endl;
}
