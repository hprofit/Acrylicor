#include "AcryEvent.h"
#include <unordered_map>

static std::unordered_map<String, EventType> TitleMap = {
	{ "nextLevel", EventType::NEXT_LEVEL },
	{ "restartLevel", EventType::RESTART_LEVEL },
	{ "loadLevel", EventType::LOAD_LEVEL },
	{ "unloadLevel", EventType::UNLOAD_LEVEL },
	{ "gameOver", EventType::GAME_OVER },

	{ "dataAmount", EventType::DATA_AMOUNT },
	{ "goDestroyed", EventType::GO_DESTROYED },
	{ "enemyDestroyed", EventType::ENEMY_DESTROYED },
	{ "bossDestroyed", EventType::BOSS_DESTROYED },

	{ "collide", EventType::COLLIDE },
	{ "collideKillZone", EventType::COLLIDE_KILL_ZONE },
	{ "reflect", EventType::REFLECT },
	{ "pushFromBody", EventType::PUSH_FROM_BODY },

	{ "keyPress", EventType::KEY_PRESS },
	{ "keyReleased", EventType::KEY_RELEASED },
	{ "keyTriggered", EventType::KEY_TRIGGERED },
	{ "mouseMotion", EventType::MOUSE_MOTION },

	{ "damage", EventType::DAMAGE },
	{ "useEnergy", EventType::USE_ENERGY },
	{ "lifeChange", EventType::LIFE_CHANGE },
	{ "playerDeath", EventType::PLAYER_DEATH },
	{ "respawn", EventType::RESPAWN },
	{ "spawn", EventType::SPAWN },
	{ "missileFired", EventType::MISSILE_FIRED },
	{ "missileAdded", EventType::MISSILE_ADDED },
	{ "missileCountChange", EventType::MISSILE_COUNT_CHANGE },
	{ "dash", EventType::DASH },
	{ "targetFound", EventType::TARGET_FOUND },
	{ "pickup", EventType::PICKUP },
	{ "shake", EventType::SHAKE },
	{ "score", EventType::SCORE },
	{ "addScore", EventType::ADD_SCORE }
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
