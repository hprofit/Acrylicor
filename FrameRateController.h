/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.h
Purpose: Provides timer functionality to the engine
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/7/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

#define MIN_FRAME_TIME 0.01666666666666666666666666666667

#include <chrono>

class FrameRateController
{
private:
	FrameRateController();
	~FrameRateController();

	std::chrono::steady_clock::time_point m_now;
	long m_deltaTime;
public:
	FrameRateController(FrameRateController const&) = delete;
	void operator=(FrameRateController const&) = delete;

	static FrameRateController& getInstance()
	{
		static FrameRateController instance;
		return instance;
	}

	long GetFrameTime() const;

	void Tick();
};

#endif