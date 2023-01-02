#include "main.h"
#include "ButtonGroup.h"



ButtonGroup::ButtonGroup(GameObject* owner):
	UIGroupControl(owner)
{
}

void ButtonGroup::Update()
{
	//choose button by mouse or keyboard
	//mouse
	{

	}

	//keyboard
	{

	}
}

void ButtonGroup::AddButton(Button* btn)
{
	m_Buttons.emplace_back(btn);
}