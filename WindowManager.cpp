#include "WindowManager.h"
#include <glew.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>

WindowManager::WindowManager(int width, int height, const char * title) : m_width(width), m_height(height)
{
	Init(title);
}

WindowManager::~WindowManager()
{
	SDL_GL_DeleteContext(m_context);
	SDL_Quit();
}

void WindowManager::Init(const char * title)
{
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle("Acrylicor Engine");
	}

	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow(title, 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		m_width, m_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	m_context = SDL_GL_CreateContext(m_window);
}

void WindowManager::SetWindowSize(int width, int height)
{
	m_width = width;
	m_height = height;
	SDL_SetWindowSize(m_window, width, height);
	glViewport(0, 0, width, height);
}

void WindowManager::SetWindowTitle(const char * title)
{
	SDL_SetWindowTitle(m_window, title);
}

void WindowManager::FrameStart(){}

void WindowManager::FrameEnd()
{
	SDL_GL_SwapWindow(m_window);
}

void WindowManager::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
	glViewport(0, 0, width, height);
}

float WindowManager::GetAspectRatio() const
{
	return (float)m_width / (float)m_height;
}
