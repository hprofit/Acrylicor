#include "InputManager.h"
#include <SDL.h>
#include "SDL_keyboard.h"
#include <string.h>
#include <stdio.h>

InputManager::InputManager() :
	m_currentState(SDL_GetKeyboardState(&m_length))
{
	m_prevState = new Uint8[m_length];
	memset(m_prevState, 0, m_length * sizeof(Uint8));
}

InputManager::~InputManager()
{ 
	//delete m_currentState;
	//delete m_prevState;
}

void InputManager::Update()
{
	memcpy(m_prevState, m_currentState, m_length * sizeof(Uint8));
	SDL_PumpEvents();

	/*SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			done = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				done = true;
			else
				client->keypress(event.key.keysym.sym, previousDeltaTime);
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				client->resize(event.window.data1, event.window.data2);
			break;
		case SDL_MOUSEMOTION:
			if ((event.motion.state&SDL_BUTTON_LMASK) != 0
				|| (event.motion.state&SDL_BUTTON_RMASK) != 0)
				client->mousedrag(event.motion.xrel, event.motion.yrel,
				(event.motion.state&SDL_BUTTON_LMASK) != 0);
			break;
		}
	}*/
}

bool InputManager::IsKeyPressed(unsigned int KeyScanCode)
{
	if (KeyScanCode >= m_length)
		return false;
	return m_currentState[KeyScanCode];
}

bool InputManager::IsKeyTriggered(unsigned int KeyScanCode)
{
	if (KeyScanCode >= m_length)
		return false;
	return (m_currentState[KeyScanCode] && !m_prevState[KeyScanCode]);
}

bool InputManager::IsKeyReleased(unsigned int KeyScanCode)
{
	if (KeyScanCode >= m_length)
		return false;
	return (!m_currentState[KeyScanCode] && m_prevState[KeyScanCode]);
}