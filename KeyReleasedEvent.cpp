#include "KeyReleasedEvent.h"

KeyReleasedEvent::KeyReleasedEvent(double time, Uint8 keyCode) :
	AcryEvent(EventType::KEY_RELEASED, time),
	m_keyCode(keyCode)
{
}

KeyReleasedEvent::~KeyReleasedEvent()
{
}
