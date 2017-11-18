#include "CollideKillZoneEvent.h"

CollideKillZoneEvent::CollideKillZoneEvent(double time, GameObject * go) :
	AcryEvent(EventType::COLLIDE_KILL_ZONE, time),
	gameObject(go) {}

CollideKillZoneEvent::~CollideKillZoneEvent() {}
