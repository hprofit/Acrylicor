/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: WindowManager.h
Purpose: Manages spawning the game window. Singleton class.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/13/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL.h>
#include "AcrylicorTypedefs.h"

class WindowManager
{
private:
	int m_width, m_height;
	SDL_GLContext m_context;
	SDL_Window * m_window;

	WindowManager();
	WindowManager(int width, int height, String title);
	~WindowManager();

	void _Init(String title);
public:
	WindowManager(const WindowManager &) = delete;
	void operator=(const WindowManager &) = delete;

	static WindowManager& GetInstance(int width = 800, int height = 600, String title = "Acrylicor")
	{
		static WindowManager instance(width, height, title);
		return instance;
	}

	SDL_Window& GetWindow() { return *m_window; }
	void SetWindowSize(int width, int height);
	void SetWindowTitle(String title);

	void FrameStart();
	void FrameEnd();
	void Resize(int width, int height);
	int WindowWidth() { return m_width; }
	int WindowHeight() { return m_height; }
	float GetAspectRatio() const;
};

#endif