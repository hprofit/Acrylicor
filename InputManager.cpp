#include "InputManager.h"
#include "SDL.h"
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