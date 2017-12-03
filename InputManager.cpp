#include "InputManager.h"

#include "EventManager.h"
#include "KeyPressEvent.h"

#include <SDL.h>
#include "SDL_keyboard.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

InputManager::InputManager()
{
	SDL_GetKeyboardState(&m_length);

	m_currentState = new Uint8[m_length];
	m_prevState = new Uint8[m_length];

	memset(m_currentState, 0, m_length * sizeof(Uint8));
	memset(m_prevState, 0, m_length * sizeof(Uint8));
}

InputManager::~InputManager()
{ 
	//delete m_currentState;
	//delete m_prevState;
}

void InputManager::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			break;

		//case SDL_WINDOWEVENT:
		//	if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		//		client->resize(event.window.data1, event.window.data2);
		//	break;
		case SDL_MOUSEBUTTONDOWN:
			if ((event.motion.state&SDL_BUTTON_LMASK) != 0 || (event.motion.state&SDL_BUTTON_RMASK) != 0)
				std::cout << "Mouse button clicked." << std::endl;
			break;
		case SDL_MOUSEMOTION:
			std::cout << "Mouse motion." << std::endl;
				//client->mousedrag(event.motion.xrel, event.motion.yrel, (event.motion.state&SDL_BUTTON_LMASK) != 0);
			break;
		}
	}

	memcpy(m_prevState, m_currentState, m_length * sizeof(Uint8));
	memcpy(m_currentState, SDL_GetKeyboardState(&m_length), m_length * sizeof(Uint8));
}

bool InputManager::IsKeyPressed(unsigned int KeyScanCode)
{
	if (KeyScanCode >= m_length)
		return false;
	return m_currentState[KeyScanCode] ? true : false;
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

void InputManager::KeyPressed(unsigned int KeyScanCode)
{
	EventManager::GetInstance().BroadcastEventToSubscribers(new KeyPressEvent(0.0, KeyScanCode));
}

void InputManager::KeyTriggered(unsigned int KeyScanCode)
{

}

void InputManager::KeyReleased(unsigned int KeyScanCode)
{

}
