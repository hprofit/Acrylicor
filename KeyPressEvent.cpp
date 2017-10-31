#include "KeyPressEvent.h"

KeyPressEvent::KeyPressEvent(unsigned int time, Uint8 keyCode) :
	AcryEvent(time, "KeyPress"),
	m_keyCode(keyCode) 
{};

KeyPressEvent::~KeyPressEvent()
{
}

void KeyPressEvent::Process(std::vector<void(*)(AcryEvent*)> listeners)
{
	for (int i = 0; i < listeners.size(); ++i) {
		listeners[i](this);
	}
}
