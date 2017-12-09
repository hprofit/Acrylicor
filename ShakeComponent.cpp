#include "ShakeComponent.h"
#include "JsonReader.h"
#include "CollideKillZoneEvent.h"

#include "TransformComponent.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ShakeEvent.h"
#include "Math3D.h"
#include <iostream>

ShakeComponent::ShakeComponent(GameObject & parent, float shakeAmount) :
	Component(parent, COMPONENT_TYPE::SHAKE),
	m_shakeDuration(0.0),
	m_currentShake(0.0),
	m_shakeAmount(shakeAmount),
	m_isShaking(false),
	m_originalPosition(Vector3D()) {}

ShakeComponent::ShakeComponent(const ShakeComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::SHAKE),
	m_shakeDuration(rhs.m_shakeDuration),
	m_currentShake(rhs.m_currentShake),
	m_shakeAmount(rhs.m_shakeAmount),
	m_isShaking(rhs.m_isShaking),
	m_originalPosition(rhs.m_originalPosition) {}

ShakeComponent::~ShakeComponent(){}

void ShakeComponent::Update(double deltaTime)
{
	if (m_isShaking) {
		m_currentShake += deltaTime;
		if (m_currentShake < m_shakeDuration) {
			float currJitterAmount = float((m_shakeDuration - m_currentShake) / m_shakeDuration);
			Vector3D jitter = Vector3D(GetRandomFloat(-1.f, 1.f), GetRandomFloat(-1.f, 1.f), 0);
			jitter = Vector3D::Normalize(jitter) * (currJitterAmount * m_shakeAmount);
			m_tComp->SetPosition(m_originalPosition + jitter);
		}
		else {
			m_isShaking = false;
			m_tComp->SetPosition(m_originalPosition);
		}
	}
}

ShakeComponent * ShakeComponent::Clone(GameObject & parent)
{
	ShakeComponent* comp = new ShakeComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	comp->_AddSubscriberToTracker();
	return comp;
}

Component * ShakeComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	ShakeComponent* comp = new ShakeComponent(gObject, AcryJson::ParseFloat(j, "shake", "amount"));
	comp->_ParseEvents(j, "shake");
	return comp;
}

void ShakeComponent::Override(nlohmann::json j)
{
	m_shakeAmount = AcryJson::ValueExists(j, "shake", "amount") ? AcryJson::ParseFloat(j, "shake", "amount") : m_shakeAmount;
}

void ShakeComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::SHAKE:
	{
		ShakeEvent * sEvent = static_cast<ShakeEvent*>(aEvent);
		m_shakeDuration = sEvent->Duration();
		m_currentShake = 0.0;
		m_originalPosition = m_tComp->GetPosition();
		m_isShaking = true;
	}
	break;
	}
}

void ShakeComponent::LateInitialize()
{
	m_tComp = static_cast<TransformComponent*>(m_parent.Get(COMPONENT_TYPE::TRANSFORM));
	if (!m_tComp)
		std::cout << "Shake components require transform components." << std::endl;
}