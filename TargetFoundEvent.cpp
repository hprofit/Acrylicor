#include "TargetFoundEvent.h"

TargetFoundEvent::TargetFoundEvent(GameObject* target) :
	AcryEvent(EventType::TARGET_FOUND),
	m_target(target)
{}

TargetFoundEvent::~TargetFoundEvent()
{
}
