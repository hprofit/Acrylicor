#include "UI_EnergyComponent.h"
#include "JsonReader.h"

#include "GameObject.h"
#include "TextComponent.h"
#include <string>
#include "DataChangeEvent.h"

void UI_EnergyComponent::_SetText() const
{
	TextComponent * tComp = static_cast<TextComponent*>(m_parent.Get(COMPONENT_TYPE::TEXT));
	tComp->SetText(m_baseMessage + std::to_string(m_energy));
}

UI_EnergyComponent::UI_EnergyComponent(GameObject & parent, String baseMessage) :
	Component(parent, COMPONENT_TYPE::UI_ENERGY),
	m_energy(0),
	m_baseMessage(baseMessage) {}

UI_EnergyComponent::UI_EnergyComponent(const UI_EnergyComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::UI_ENERGY),
	m_energy(rhs.m_energy),
	m_baseMessage(rhs.m_baseMessage) {}

UI_EnergyComponent::~UI_EnergyComponent()
{
}

void UI_EnergyComponent::Update(double deltaTime)
{
}

UI_EnergyComponent * UI_EnergyComponent::Clone(GameObject & parent)
{
	UI_EnergyComponent* comp = new UI_EnergyComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * UI_EnergyComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	UI_EnergyComponent* comp = new UI_EnergyComponent(gObject,
		AcryJson::ParseString(j, "uiEnergy", "baseMessage")
	);
	comp->_ParseEvents(j, "uiEnergy");

	return comp;
}

void UI_EnergyComponent::Override(nlohmann::json j)
{
	m_baseMessage = AcryJson::ValueExists(j, "uiMissiles", "baseMessage") ? AcryJson::ParseString(j, "uiMissiles", "baseMessage") : m_baseMessage;
}

void UI_EnergyComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::DATA_AMOUNT:
	{
		DataChangeEvent<int>* dcEvent = static_cast<DataChangeEvent<int>*>(aEvent);

		if (dcEvent && dcEvent->Type() == "energy") {
			m_energy = dcEvent->Data();
			_SetText();
		}
	}
		break;
	}
}

void UI_EnergyComponent::LateInitialize()
{
	_SetText();
}
