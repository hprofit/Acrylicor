/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LevelManager.h
Purpose: Manages which level is loaded.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/02/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "Subscriber.h"
#include "EventManager.h"
#include "AcryEvent.h"
#include "GameObjectManager.h"
#include "AcrylicorTypedefs.h"
#include "GameObject.h"
#include <map>
#include <string>
#include <vector>
#include <utility>

class LevelManager : 
	public Subscriber
{
private:
	EventManager& _EventManager;
	GameObjectManager& _GameObjectManager;

	unsigned int m_currentLevel;
	unsigned int m_lastLevel;
	std::vector<String> m_levels;

	LevelManager();
	~LevelManager();
public:
	LevelManager(const LevelManager &) = delete;
	void operator=(const LevelManager &) = delete;

	static LevelManager& GetInstance()
	{
		static LevelManager instance;
		return instance;
	}

	virtual void HandleEvent(AcryEvent * aEvent);

	void LoadLevelConfig(String fileName);
	void LoadLevel(String fileName);

	void LoadCurrentLevel();
	void LoadNextLevel();
};

#endif