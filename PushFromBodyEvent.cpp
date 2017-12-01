#include "PushFromBodyEvent.h"


PushFromBodyEvent::PushFromBodyEvent(Contact _contact) :
	AcryEvent(EventType::PUSH_FROM_BODY),
	m_contact(_contact)
{
}

PushFromBodyEvent::~PushFromBodyEvent()
{
}
