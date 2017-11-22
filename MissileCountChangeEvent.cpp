#include "MissileCountChangeEvent.h"

MissileCountChangeEvent::MissileCountChangeEvent(double time, int _count) :
	AcryEvent(EventType::MISSILE_COUNT_CHANGE, time),
	count(_count)
{
}

MissileCountChangeEvent::~MissileCountChangeEvent()
{
}

int MissileCountChangeEvent::Count() const
{
	return count;
}
