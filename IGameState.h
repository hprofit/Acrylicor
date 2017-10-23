/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: IGameState.h
Purpose: Game State interface -- provides list of functions that should be implemented for use with the engine.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef IGAMESTATE_H
#define IGAMESTATE_H

class IGameState
{
protected:
	IGameState() {};
public:
	virtual ~IGameState(void) {};

	virtual void GameStateLoad(void) = 0;
	virtual void GameStateInit(void) = 0;
	virtual void GameStateUpdate(double deltaTime = 0.0) = 0;
	virtual void GameStateDraw(void) = 0;
	virtual void GameStateFree(void) = 0;
	virtual void GameStateUnload(void) = 0;
};


#endif