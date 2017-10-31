/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: InputManager.h
Purpose: Provides all input related funcionality.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "AcrylicorTypedefs.h"
#include "SDL_keycode.h"

enum ACR_KEY {
	ACR_A = SDL_SCANCODE_A,
	ACR_B = SDL_SCANCODE_B,
	ACR_C = SDL_SCANCODE_C,
	ACR_D = SDL_SCANCODE_D,
	ACR_E = SDL_SCANCODE_E,
	ACR_F = SDL_SCANCODE_F,
	ACR_G = SDL_SCANCODE_G,
	ACR_H = SDL_SCANCODE_H,
	ACR_I = SDL_SCANCODE_I,
	ACR_J = SDL_SCANCODE_J,
	ACR_K = SDL_SCANCODE_K,
	ACR_L = SDL_SCANCODE_L,
	ACR_M = SDL_SCANCODE_M,
	ACR_N = SDL_SCANCODE_N,
	ACR_O = SDL_SCANCODE_O,
	ACR_P = SDL_SCANCODE_P,
	ACR_Q = SDL_SCANCODE_Q,
	ACR_R = SDL_SCANCODE_R,
	ACR_S = SDL_SCANCODE_S,
	ACR_T = SDL_SCANCODE_T,
	ACR_U = SDL_SCANCODE_U,
	ACR_V = SDL_SCANCODE_V,
	ACR_W = SDL_SCANCODE_W,
	ACR_X = SDL_SCANCODE_X,
	ACR_Y = SDL_SCANCODE_Y,
	ACR_Z = SDL_SCANCODE_Z,
	ACR_UP = SDL_SCANCODE_UP,
	ACR_DOWN = SDL_SCANCODE_DOWN,
	ACR_LEFT = SDL_SCANCODE_LEFT,
	ACR_RIGHT = SDL_SCANCODE_RIGHT,
	ACR_SPACE = SDL_SCANCODE_SPACE,
	ACR_ENTER = SDL_SCANCODE_RETURN,
	ACR_ESCAPE = SDL_SCANCODE_ESCAPE,
	ACR_0 = SDL_SCANCODE_0,
	ACR_1 = SDL_SCANCODE_1,
	ACR_2 = SDL_SCANCODE_2,
	ACR_3 = SDL_SCANCODE_3,
	ACR_4 = SDL_SCANCODE_4,
	ACR_5 = SDL_SCANCODE_5,
	ACR_6 = SDL_SCANCODE_6,
	ACR_7 = SDL_SCANCODE_7,
	ACR_8 = SDL_SCANCODE_8,
	ACR_9 = SDL_SCANCODE_9
};

class InputManager
{
private:
	Uint8 * m_prevState;
	Uint8 * m_currentState;

	int m_length;

	InputManager();
	~InputManager();

public:
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	void Update();
	bool IsKeyPressed(unsigned int KeyScanCode);
	bool IsKeyTriggered(unsigned int KeyScanCode);
	bool IsKeyReleased(unsigned int KeyScanCode);

	void KeyPressed(unsigned int KeyScanCode);
	void KeyTriggered(unsigned int KeyScanCode);
	void KeyReleased(unsigned int KeyScanCode);
};

#endif