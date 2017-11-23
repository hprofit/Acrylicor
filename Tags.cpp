#include "Tags.h"

Tags::Tags(){}

Tags::Tags(const Tags & rhs) : m_tags(rhs.m_tags) {}

Tags & Tags::operator=(const Tags & rhs)
{
	m_tags = rhs.m_tags;
	return *this;
}

Tags::~Tags(){}

void Tags::AddTag(String tag)
{
	m_tags.push_back(tag);
}

bool Tags::HasTag(String tag) const
{
	for (String mTag : m_tags) {
		if (mTag.compare(tag) == 0)
			return true;
	}
	return false;
}

void Tags::RemoveTag(String tag)
{
	m_tags.remove(tag);
}

void Tags::SetTags(std::list<String> tags)
{
	m_tags = tags;
}

std::list<String> Tags::GetTags() const
{
	return m_tags;
}