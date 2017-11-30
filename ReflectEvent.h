/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ReflectEvent.h
Purpose: Event that indicates a reflection should happen following a collision between GameObjects
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/26/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef REFLECT_EVENT_H
#define REFLECT_EVENT_H

#include "AcryEvent.h"
#include "Contact.h"

class GameObject;

class ReflectEvent :
	public AcryEvent
{
private:
	Contact m_contact;

public:
	ReflectEvent(Contact _contact);
	virtual ~ReflectEvent();

	Contact GetContact() { return m_contact; }
};

#endif
