#include "ShakeEvent.h"

ShakeEvent::ShakeEvent(double _duration) :
	AcryEvent(EventType::SHAKE),
	duration(_duration){}

ShakeEvent::~ShakeEvent() {}
