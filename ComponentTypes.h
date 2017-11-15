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
	TRANSFORM,
	CONTROLLER,
	AI_SWAY,
	AI_RUSH,
	WEAPON,
	CAMERA,

	NUM_COMPONENTS
};

#endif
