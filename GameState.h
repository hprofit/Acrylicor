/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mesh.h
Purpose: Provides a collection of buffers that make up a Mesh
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 9/29/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

class IGameState
{
public:
	virtual ~IGameState(void) {};

	virtual void GameStateLoad(void) = 0;
	virtual void GameStateInit(void) = 0;
	virtual void GameStateUpdate(void) = 0;
	virtual void GameStateDraw(void) = 0;
	virtual void GameStateFree(void) = 0;
	virtual void GameStateUnload(void) = 0;
};


#endif