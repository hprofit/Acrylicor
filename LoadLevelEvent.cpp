#include "LoadLevelEvent.h"

LoadLevelEvent::LoadLevelEvent(double time, unsigned int _level) :
	AcryEvent(EventType::LOAD_LEVEL, time),
	level(_level) {}

LoadLevelEvent::~LoadLevelEvent()
{
}
