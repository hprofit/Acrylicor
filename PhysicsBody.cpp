#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(BODY_TYPE type) : 
	m_type(type) 
{};

PhysicsBody::PhysicsBody(const PhysicsBody & rhs) :
	m_tags(rhs.m_tags), 
	m_type(rhs.m_type) 
{}
Tags & PhysicsBody::Tags()
{
	return m_tags;
}
