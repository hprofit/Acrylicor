/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollideEvent.h
Purpose: Event that indicates a collision between GameObjects
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef COLLIDE_EVENT_H
#define COLLIDE_EVENT_H

#include "AcryEvent.h"
#include "Contact.h"

class GameObject;

class CollideEvent :
	public AcryEvent
{
private:
	Contact m_contact;

public:
	CollideEvent(Contact _contact);
	virtual ~CollideEvent();

	Contact GetContact() { return m_contact; }
};

#endif
