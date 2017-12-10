/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AddScoreEvent.h
Purpose: Event that indicates an amount of points to add to the player's score
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef ADD_SCORE_EVENT_H
#define ADD_SCORE_EVENT_H

#include "AcryEvent.h"
#include "Contact.h"

class GameObject;

class AddScoreEvent :
	public AcryEvent
{
private:
	int scoreAmount;
	GameObject* gameObject;

public:
	AddScoreEvent(int _scoreAmount, GameObject* _gameObject);
	virtual ~AddScoreEvent();

	int Score() { return scoreAmount; }
	GameObject* GO() const { return gameObject; }
};

#endif
