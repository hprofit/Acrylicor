#include "PickupEvent.h"

PickupEvent::PickupEvent(PICKUP_TYPE _pickup) :
	AcryEvent(EventType::PICKUP),
	pickup(_pickup)
{}

PickupEvent::~PickupEvent()
{
}
