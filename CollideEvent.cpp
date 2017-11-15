#include "CollideEvent.h"

CollideEvent::CollideEvent(double time, GameObject * _lhs, GameObject * _rhs) :
	AcryEvent(EventType::COLLIDE, time),
	lhs(_lhs),
	rhs(_rhs)
{
}

CollideEvent::~CollideEvent()
{
}

