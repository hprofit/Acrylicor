#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(BODY_TYPE type) : 
	m_type(type) 
{};

PhysicsBody::PhysicsBody(const PhysicsBody & rhs) :
	m_tags(rhs.m_tags), 
	m_type(rhs.m_type) 
{};

void PhysicsBody::AddTag(String tag)
{
	m_tags.push_back(tag);
}

bool PhysicsBody::HasTag(String tag) const
{
	for (String mTag : m_tags) {
		if (mTag.compare(tag) == 0)
			return true;
	}
	return false;
}

void PhysicsBody::RemoveTag(String tag)
{
	m_tags.remove(tag);
}

void PhysicsBody::SetTags(std::list<String> tags)
{
	m_tags = tags;
}

std::list<String> PhysicsBody::GetTags() const
{
	return m_tags;
}