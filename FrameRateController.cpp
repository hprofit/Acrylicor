#include "FrameRateController.h"

FrameRateController::FrameRateController()
{
	m_now = std::chrono::steady_clock::now();
	m_deltaTime = MIN_FRAME_TIME;
}

FrameRateController::~FrameRateController() { }

long FrameRateController::GetFrameTime() const
{
	return m_deltaTime;
}

void FrameRateController::Tick()
{
	std::chrono::steady_clock::time_point newNow = std::chrono::steady_clock::now();
	m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(newNow - m_now).count();
}
