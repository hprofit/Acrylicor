#include "LifeChangeEvent.h"



LifeChangeEvent::LifeChangeEvent(double time, bool gain, int amount) :
	AcryEvent(EventType::LIFE_CHANGE, time),
	m_gain(gain), m_amt(amount){}


LifeChangeEvent::~LifeChangeEvent()
{
}
