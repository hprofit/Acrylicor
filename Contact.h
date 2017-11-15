/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Contact.h
Purpose: Contact data between two PhysicsBody objects
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/03/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef CONTACT_H
#define CONTACT_H

class PhysicsBody;
class GameObject;

class Contact
{
protected:
	GameObject * m_lhsGO;
	GameObject * m_rhsGO;
public:
	Contact(GameObject* lhsGO, GameObject* rhsGO) :
		m_lhsGO(lhsGO), m_rhsGO(rhsGO) {};
	virtual ~Contact() {};

	GameObject * LHS_GO() const { return m_lhsGO; }
	GameObject * RHS_GO() const { return m_rhsGO; }
};

#endif