#include "EnergyComponent.h"
#include "JsonReader.h"
#include "EventManager.h"
#include "DataChangeEvent.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <algorithm>

EnergyComponent::EnergyComponent(GameObject & parent, float maxEnergy, float rechargeRate) :
	Component(parent, COMPONENT_TYPE::ENERGY),
	m_energy(maxEnergy),
	m_maxEnergy(maxEnergy),
	m_rechargeRate(rechargeRate) {}

EnergyComponent::EnergyComponent(const EnergyComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::ENERGY),
	m_energy(rhs.m_energy),
	m_maxEnergy(rhs.m_maxEnergy),
	m_rechargeRate(rhs.m_rechargeRate) {}

EnergyComponent::~EnergyComponent()
{
}

void EnergyComponent::Update(double deltaTime)
{
	if (m_energy < m_maxEnergy) {
		m_energy = std::min(m_energy + ((float)deltaTime * m_rechargeRate), m_maxEnergy);
		EventManager::GetInstance().BroadcastEventToSubscribers(new DataChangeEvent<int>(0.0, "energy", std::floor(m_energy)));
	}
}

EnergyComponent * EnergyComponent::Clone(GameObject & parent)
{
	EnergyComponent* comp = new EnergyComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * EnergyComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new EnergyComponent(gObject, 
		AcryJson::ParseFloat(j, "energy", "max"),
		AcryJson::ParseFloat(j, "energy", "rate")
		);
}

void EnergyComponent::Override(nlohmann::json j)
{
	m_maxEnergy = AcryJson::ValueExists(j, "energy", "max") ? AcryJson::ParseFloat(j, "energy", "max") : m_maxEnergy;
	m_rechargeRate = AcryJson::ValueExists(j, "energy", "rate") ? AcryJson::ParseFloat(j, "energy", "rate") : m_rechargeRate;

	m_energy = m_maxEnergy;
}

void EnergyComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	}
}

void EnergyComponent::LateInitialize()
{
	EventManager::GetInstance().BroadcastEventToSubscribers(new DataChangeEvent<int>(0.1, "energy", m_energy));
}

bool EnergyComponent::EnoughEnergy(float energyRequired) const
{
	return m_energy >= energyRequired;
}

void EnergyComponent::UseEnergy(float amount)
{
	m_energy -= amount;
	EventManager::GetInstance().BroadcastEventToSubscribers(new DataChangeEvent<int>(0.0, "energy", -amount));
}
