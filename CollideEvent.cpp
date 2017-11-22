#include "CollideEvent.h"

CollideEvent::CollideEvent(Contact _contact) :
	AcryEvent(EventType::COLLIDE),
	m_contact(_contact)
{}

CollideEvent::~CollideEvent()
{
}

