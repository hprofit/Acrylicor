/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TestGameState.h
Purpose: Test Game state, for use in testing the engine.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/22/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef TEST_GAMESTATE_H
#define TEST_GAMESTATE_H

#include "IGameState.h"
#include <glew.h>
#include <GL/gl.h>

class TestGameState :
	public IGameState
{
public:
	GLint	program,
		aposition,
		anormal,
		upersp_matrix,
		uview_matrix,
		umodel_matrix,
		unormal_matrix,
		ucolor;

	TestGameState();
	virtual ~TestGameState();

	virtual void GameStateLoad(void);
	virtual void GameStateInit(void);
	virtual void GameStateUpdate(double deltaTime = 0.0);
	virtual void GameStateDraw(void);
	virtual void GameStatePostUpdate(void);
	virtual void GameStateFree(void);
	virtual void GameStateUnload(void);
};

#endif