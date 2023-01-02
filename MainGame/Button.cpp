#include "main.h"
#include "Button.h"

Button::Button(GameObject* owner, int order):
Component(owner,order),
m_State(IDLE)
{
}

void Button::SetState(State next)
{
	if (next == m_State)
	{
		return;
	}

	if (m_State == IDLE && next == HIGHLIGHTED)
	{
		OnEnter();
	}
	
	if (m_State == HIGHLIGHTED && next == IDLE)
	{
		OnExit();
	}

	m_State = next;
}

void Button::OnClick()
{
	for (auto func: m_OnClicks)
	{
		func();
	}
}

void Button::OnEnter()
{
	for (auto func : m_OnEnters)
	{
		func();
	}
}

void Button::OnExit()
{
	for (auto func : m_OnExits)
	{
		func();
	}
}

void Button::AddClickEvent(std::function<void()> onClick)
{
	m_OnClicks.emplace_back(onClick);
}

void Button::AddEnterEvent(std::function<void()> onEnter)
{
	m_OnEnters.emplace_back(onEnter);
}

void Button::AddExitEvent(std::function<void()> onExit)
{
	m_OnExits.emplace_back(onExit);
}

