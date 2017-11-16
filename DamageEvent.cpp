#include "DamageEvent.h"

DamageEvent::DamageEvent(double time, int dmgAmt) :
	AcryEvent(EventType::DAMAGE, time),
	damageAmt(dmgAmt) {}

DamageEvent::~DamageEvent()
{
}
