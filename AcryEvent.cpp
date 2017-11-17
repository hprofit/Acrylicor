#include "AcryEvent.h"

static std::unordered_map<String, EventType> TitleMap = {
	{ "collide", EventType::COLLIDE },
	{ "keyPress", EventType::KEY_PRESS },
	{ "damage", EventType::DAMAGE },
	{ "lifeChange", EventType::LIFE_CHANGE },
	{ "playerDeath", EventType::PLAYER_DEATH },
	{ "respawn", EventType::RESPAWN },
};

AcryEvent::AcryEvent(EventType type) :
	m_time(0.0), m_type(type)
{}

AcryEvent::AcryEvent(EventType type, double time) :
	m_time(time), m_type(type)
{}

AcryEvent::~AcryEvent()
{
}

double AcryEvent::Time() const
{
	return m_time;
}

EventType AcryEvent::Type() const
{
	return m_type;
}

void AcryEvent::DecrementTime(double amt)
{
	m_time -= amt;
}

EventType AcryEvent::GetEventTypeFromTitle(String eventTitle)
{
	return TitleMap[eventTitle];
}
