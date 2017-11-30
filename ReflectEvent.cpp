#include "ReflectEvent.h"

ReflectEvent::ReflectEvent(Contact _contact) :
	AcryEvent(EventType::REFLECT),
	m_contact(_contact)
{}

ReflectEvent::~ReflectEvent() {}

