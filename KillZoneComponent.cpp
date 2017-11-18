#include "KillZoneComponent.h"
#include "JsonReader.h"
#include "CollideKillZoneEvent.h"

#include "PhysicsComponent.h"
#include "GameObject.h"

KillZoneComponent::KillZoneComponent(GameObject & parent) :
	Component(parent, COMPONENT_TYPE::KILL_ZONE) {}

KillZoneComponent::KillZoneComponent(const KillZoneComponent & rhs, GameObject & parent) :
	Component(parent, COMPONENT_TYPE::KILL_ZONE),
	m_tags(rhs.m_tags) {}

KillZoneComponent::~KillZoneComponent()
{
}

void KillZoneComponent::Update(double deltaTime)
{
}

KillZoneComponent * KillZoneComponent::Clone(GameObject & parent)
{
	KillZoneComponent* comp = new KillZoneComponent(*this, parent);
	comp->_SubscribeToEvents(this->m_eventsToSubscribeTo);
	return comp;
}

Component * KillZoneComponent::Serialize(GameObject & gObject, nlohmann::json j)
{
	KillZoneComponent * kComp = new KillZoneComponent(gObject);
	if (AcryJson::ValueExists(j, "killZone", "tags"))
		kComp->SetTags(j["killZone"]["tags"]);
	return kComp;
}

void KillZoneComponent::Override(nlohmann::json j)
{
	if (AcryJson::ValueExists(j, "killZone", "tags"))
		SetTags(j["killZone"]["tags"]);
}

void KillZoneComponent::HandleEvent(AcryEvent * aEvent)
{
	switch (aEvent->Type()) {
	case EventType::COLLIDE_KILL_ZONE:
	{
		CollideKillZoneEvent * cpEvent = static_cast<CollideKillZoneEvent*>(aEvent);
		PhysicsComponent * pComp = static_cast<PhysicsComponent*>(cpEvent->GO()->Get(COMPONENT_TYPE::PHYSICS));
		
		for (String tag : m_tags) {
			if (pComp->Body().HasTag(tag)) {
				cpEvent->GO()->Kill();
				return;
			}
		}
	}
	break;
	}
}

#pragma region Tags

void KillZoneComponent::AddTag(String tag)
{
	m_tags.push_back(tag);
};

bool KillZoneComponent::HasTag(String tag) const
{
	for (String mTag : m_tags) {
		if (mTag.compare(tag) == 0)
			return true;
	}
	return false;
};

void KillZoneComponent::RemoveTag(String tag)
{
	m_tags.remove(tag);
};

void KillZoneComponent::SetTags(std::list<String> tags)
{
	m_tags = tags;
}

#pragma endregion