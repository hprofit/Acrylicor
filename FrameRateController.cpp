#include "FrameRateController.h"
#include <algorithm>
#include "SDL_timer.h"

#define MIN_FRAME_TIME 0.01666666666666666666666666666667

FrameRateController::FrameRateController(unsigned int maxFrameRate) :
	m_deltaTime(MIN_FRAME_TIME),
	m_maxFrameRate(maxFrameRate),
	m_ticksPerFrame(1000.0f / (float)m_maxFrameRate),
	m_tickStart(0),
	m_tickEnd(0)
{ }

FrameRateController::~FrameRateController() { }

double FrameRateController::GetFrameTime() const
{
	return m_deltaTime;
}

void FrameRateController::FrameStart()
{
	m_tickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd()
{
	m_tickEnd = SDL_GetTicks();

	while (m_tickEnd - m_tickStart < m_ticksPerFrame)
		m_tickEnd = SDL_GetTicks();

	m_deltaTime = std::max((float)(m_tickEnd - m_tickStart), m_ticksPerFrame) / 1000.0;
}

unsigned int FrameRateController::GetTime()
{
	//return SDL_GetTicks();
	return 0;
}
