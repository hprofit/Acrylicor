#include "MouseMotionEvent.h"

MouseMotionEvent::MouseMotionEvent(double time) :
	AcryEvent(EventType::MOUSE_MOTION, time)
{
}

MouseMotionEvent::~MouseMotionEvent()
{
}
