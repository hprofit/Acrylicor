/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PickupTypes.h
Purpose: Provides an enum for all possible picup types 
other types of Components.
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 12/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PICKUP_TYPES_H
#define PICKUP_TYPES_H

const enum class PICKUP_TYPE {
	LIFE = 0,
	DOUBLE_BARREL,
	SPLIT_BARREL,
	MISSILE
};

#endif
