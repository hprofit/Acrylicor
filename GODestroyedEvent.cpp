#include "GODestroyedEvent.h"

GODestroyedEvent::GODestroyedEvent(double time, GameObject * go) :
	AcryEvent(EventType::GO_DESTROYED, time),
	gameObject(go) {}

GODestroyedEvent::~GODestroyedEvent() {}

