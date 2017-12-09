/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TimeToLiveComponent.h
Purpose: Automatically kills the game object after the specified time has passed
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/08/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef TIME_TO_LIVE_COMPONENT_H
#define TIME_TO_LIVE_COMPONENT_H

#include "Component.h"

class TimeToLiveComponent :
	public Component
{
protected:
	double m_timeToLive;
	double m_timePassed;

public:
	TimeToLiveComponent() = delete;
	TimeToLiveComponent(GameObject& parent, double timeToLive);
	TimeToLiveComponent(const TimeToLiveComponent& rhs, GameObject& parent);
	virtual ~TimeToLiveComponent();

	virtual void Update(double deltaTime);
	virtual TimeToLiveComponent* Clone(GameObject& parent);
	static Component* Serialize(GameObject& gObject, nlohmann::json j);
	virtual void Override(nlohmann::json j);
	virtual void RegisterWithManager() {};
	virtual void HandleEvent(AcryEvent * aEvent);
};

#endif
