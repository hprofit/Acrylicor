#include "SubscriberTracker.h"
#include "Subscriber.h"
#include <algorithm>

SubscriberTracker::SubscriberTracker()
{
}

SubscriberTracker::~SubscriberTracker() {}

void SubscriberTracker::AddSubscriber(Subscriber * subscriber)
{
	m_subscribers.push_back(subscriber);
}

void SubscriberTracker::RemoveSubscriber(Subscriber * subscriber)
{
	m_subscribers.erase(
		std::remove(m_subscribers.begin(), m_subscribers.end(), subscriber),
		m_subscribers.end()
	);
}