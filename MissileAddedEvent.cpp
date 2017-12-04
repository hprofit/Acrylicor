#include "MissileAddedEvent.h"

MissileAddedEvent::MissileAddedEvent(int _missileAmt) :
	AcryEvent(EventType::MISSILE_ADDED),
	missileAmt(_missileAmt) {}

MissileAddedEvent::~MissileAddedEvent(){}
