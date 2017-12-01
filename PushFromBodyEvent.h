/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PushFromBodyEvent.h
Purpose: Event that indicates that bodies should remove themselves from one another's bodies following a collision between GameObjects
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/26/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef PUSH_FROM_BODY_EVENT_H
#define PUSH_FROM_BODY_EVENT_H

#include "AcryEvent.h"
#include "Contact.h"

class GameObject;

class PushFromBodyEvent :
	public AcryEvent
{
private:
	Contact m_contact;

public:
	PushFromBodyEvent(Contact _contact);
	virtual ~PushFromBodyEvent();

	Contact GetContact() { return m_contact; }
};

#endif
