#include "AcryEvent.h"

AcryEvent::~AcryEvent()
{
}

bool AcryEvent::operator<(const AcryEvent & rhs)
{
	return m_time < rhs.m_time;
}

bool AcryEvent::operator>(const AcryEvent & rhs)
{
	return m_time > rhs.m_time;
}

bool operator<(const AcryEvent & lhs, const AcryEvent & rhs)
{
	return lhs.m_time < rhs.m_time;
}

bool operator>(const AcryEvent & lhs, const AcryEvent & rhs)
{
	return lhs.m_time > rhs.m_time;
}
