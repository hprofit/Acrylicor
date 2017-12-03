#include "DashComponent.h"
#include "JsonReader.h"
#include "GameObject.h"
#include "AcryEvent.h"
#include "PhysicsComponent.h"
#include "EnergyComponent.h"
#include <iostream>

DashComponent::DashComponent(GameObject & parent, int energyRequired, float speed, double dashTime) :
	Component(parent, COMPONENT_TYPE::DASH),
	m_energyRequired(energyRequired), m_speed(speed),  m_maxSpeed(0.f), m_dashTime(dashTime), m_currentDashTime(0.0)
{}

DashComponent::DashComponent(const DashComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::DASH),
	m_energyRequired(rhs.m_energyRequired), m_speed(rhs.m_speed), m_maxSpeed(rhs.m_maxSpeed), m_dashTime(rhs.m_dashTime), m_currentDashTime(0.0)
{}

DashComponent::~DashComponent()
{
}

void DashComponent::Update(double deltaTime)
{
	if (m_currentDashTime > 0.0) {
		m_currentDashTime -= deltaTime;

		if (m_currentDashTime <= 0.0)
			m_pComp->SetMaxSpeed(m_maxSpeed);
	}
}

DashComponent * DashComponent::Clone(GameObject & parent)
{
	DashComponent* comp = new DashComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * DashComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new DashComponent(gObject, 
		AcryJson::ParseInt(j, "dash", "energy"),
		AcryJson::ParseFloat(j, "dash", "speed"),
		AcryJson::ParseDouble(j, "dash", "dashTime")
	);
}

void DashComponent::Override(nlohmann::json j)
{
	m_speed = AcryJson::ValueExists(j, "dash", "speed") ? AcryJson::ParseFloat(j, "dash", "speed") : m_speed;
	m_energyRequired = AcryJson::ValueExists(j, "dash", "energy") ? AcryJson::ParseInt(j, "dash", "energy") : m_energyRequired;
	m_dashTime = AcryJson::ValueExists(j, "dash", "dashTime") ? AcryJson::ParseDouble(j, "dash", "dashTime") : m_dashTime;
}

void DashComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::DASH:
	{
		if (m_eComp->EnoughEnergy(m_energyRequired)) {
			m_pComp->SetMaxSpeed(m_speed);
			m_pComp->AddForce(Vector3D::Normalize(m_pComp->GetVelocity()) * m_speed);
			m_currentDashTime = m_dashTime;
			m_eComp->UseEnergy(m_energyRequired);
		}
	}
	break;
	}
}

void DashComponent::LateInitialize()
{
	m_pComp = static_cast<PhysicsComponent*>(m_parent.Get(COMPONENT_TYPE::PHYSICS));
	m_eComp = static_cast<EnergyComponent*>(m_parent.Get(COMPONENT_TYPE::ENERGY));
	if (!m_pComp)
		std::cout << "Dash components require Physics components." << std::endl;
	if (!m_eComp)
		std::cout << "Dash components require Energy components." << std::endl;

	m_maxSpeed = m_pComp->MaxSpeed();
}
