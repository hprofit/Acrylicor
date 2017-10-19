/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.h
Purpose: Provides timer functionality to the engine. Singleton class.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/7/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

class FrameRateController
{
private:
	double m_deltaTime;
	unsigned int m_maxFrameRate;
	float m_ticksPerFrame;
	unsigned int m_tickStart;
	unsigned int m_tickEnd;

	FrameRateController(unsigned int maxFrameRate);
	~FrameRateController();
public:
	FrameRateController(FrameRateController const&) = delete;
	void operator=(FrameRateController const&) = delete;

	static FrameRateController& GetInstance(unsigned int maxFrameRate = 60)
	{
		static FrameRateController instance(maxFrameRate);
		return instance;
	}

	double GetFrameTime() const;

	void FrameStart();
	void FrameEnd();
};

#endif