#include "GameObject.h"
#include "Component.h"


Component::Component(GameObject* owner, int order):
	m_Owner(owner),
	m_UpdateOrder(order)
{
	if (m_Owner != nullptr)
	{
		m_Owner->AddComponent(this);
	}
}

Component::~Component()
{
	if (m_Owner != nullptr)
	{
		m_Owner->RemoveComponent(this);
	}
}

void Component::Update()
{
}
