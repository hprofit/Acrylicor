#include "KeyTriggeredEvent.h"

KeyTriggeredEvent::KeyTriggeredEvent(double time, Uint8 keyCode) :
	AcryEvent(EventType::KEY_TRIGGERED, time),
	m_keyCode(keyCode)
{}

KeyTriggeredEvent::~KeyTriggeredEvent()
{
}
