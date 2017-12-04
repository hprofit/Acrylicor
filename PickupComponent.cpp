#include "PickupComponent.h"
#include "JsonReader.h"

#include "AcryEvent.h"
#include "CollideEvent.h"
#include "PickupEvent.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "LifeChangeEvent.h"
#include "DataChangeEvent.h"
#include "MissileAddedEvent.h"
#include "EventManager.h"

PickupComponent::PickupComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::PICKUP)
{}

PickupComponent::PickupComponent(const PickupComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::PICKUP)
{}

PickupComponent::~PickupComponent() {}

void PickupComponent::Update(double deltaTime){}

PickupComponent * PickupComponent::Clone(GameObject & parent)
{
	PickupComponent* comp = new PickupComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * PickupComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	return new PickupComponent(gObject);
}

void PickupComponent::Override(nlohmann::json j)
{
	String type = AcryJson::ParseString(j, "pickup", "type");

	if (type == "life")
		m_pickupType = PICKUP_TYPE::LIFE;
	else if (type == "doubleBarrel")
		m_pickupType = PICKUP_TYPE::DOUBLE_BARREL;
	else if (type == "splitBarrel")
		m_pickupType = PICKUP_TYPE::SPLIT_BARREL;
	else if (type == "missile")
		m_pickupType = PICKUP_TYPE::MISSILE;

	_ParseEvents(j, "pickup");
	_SubscribeToEvents(this->m_eventsToSubscribeTo);
}

void PickupComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::PICKUP:
	{
		switch (m_pickupType) {
		case PICKUP_TYPE::LIFE:
			EventManager::GetInstance().BroadcastEventToSubscribers(new LifeChangeEvent(0.0, true, 1));
			break;
		case PICKUP_TYPE::MISSILE:
			EventManager::GetInstance().BroadcastEventToSubscribers(new MissileAddedEvent(3));
			break;
		case PICKUP_TYPE::DOUBLE_BARREL:
			EventManager::GetInstance().BroadcastEventToSubscribers(new PickupEvent(m_pickupType));
			break;
		case PICKUP_TYPE::SPLIT_BARREL:
			EventManager::GetInstance().BroadcastEventToSubscribers(new PickupEvent(m_pickupType));
			break;
		}

		GameObjectManager::GetInstance().DestroyGameObject(&m_parent);
	}
	break;
	}
}
