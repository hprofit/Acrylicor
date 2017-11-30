#include "AcryEvent.h"
#include <unordered_map>

static std::unordered_map<String, EventType> TitleMap = {
	{ "dataAmount", EventType::DATA_AMOUNT },
	{ "goDestroyed", EventType::GO_DESTROYED },
	{ "collide", EventType::COLLIDE },
	{ "collideKillZone", EventType::COLLIDE_KILL_ZONE },
	{ "keyPress", EventType::KEY_PRESS },
	{ "damage", EventType::DAMAGE },
	{ "useEnergy", EventType::USE_ENERGY },
	{ "lifeChange", EventType::LIFE_CHANGE },
	{ "playerDeath", EventType::PLAYER_DEATH },
	{ "respawn", EventType::RESPAWN },
	{ "missileFired", EventType::MISSILE_FIRED },
	{ "missileCountChange", EventType::MISSILE_COUNT_CHANGE },
	{ "dash", EventType::DASH }
};

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
