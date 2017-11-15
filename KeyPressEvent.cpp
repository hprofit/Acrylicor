#include "KeyPressEvent.h"

KeyPressEvent::KeyPressEvent(double time, Uint8 keyCode) :
	AcryEvent(EventType::KEY_PRESS, time),
	m_keyCode(keyCode) 
{};

KeyPressEvent::~KeyPressEvent()
{
}
