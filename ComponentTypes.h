/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ComponentTypes.h
Purpose: Provides an enum for all possible component types -- seperating this from Component so Component.h doesn't know about
other types of Components.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 10/20/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

const enum class COMPONENT_TYPE {
	PHYSICS = 0,
	SPRITE,
	SCROLLING_SPRITE,
	TEXT,
	TRANSFORM,
	CONTROLLER,

	AI_SQUARE_SWAY,
	AI_SWAY,
	AI_RUSH,
	AI_SEEK,
	AI_AREA_OF_SIGHT,
	AI_FIRE_GUN,

	WEAPON,
	MISSILE_LAUNCHER,
	CAMERA,
	SPAWNER,

	HEALTH,
	ENERGY,
	DAMAGE,
	KILL_ZONE,
	DASH,

	GOAL,
	PICKUP,

	UI_LIVES,
	UI_SCORE,
	UI_MISSILES,
	UI_ENERGY,

	NUM_COMPONENTS
};

#endif
