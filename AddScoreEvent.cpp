#include "AddScoreEvent.h"

AddScoreEvent::AddScoreEvent(int _scoreAmount, GameObject* _gameObject) :
	AcryEvent(EventType::ADD_SCORE),
	scoreAmount(_scoreAmount),
	gameObject(_gameObject)
{}

AddScoreEvent::~AddScoreEvent(){}

