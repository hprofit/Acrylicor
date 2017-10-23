/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.h
Purpose: Base Player class - For testing
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/20/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Vector2D.h"
#include <string>

class Player :
	public GameObject
{
public:
	Player();
	Player(Player const& rhs);
	~Player();

	virtual void Update();
	virtual void Update(double deltaTime);
};

#endif