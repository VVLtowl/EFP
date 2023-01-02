#include "main.h"
#include "UIGroupControl.h"

UIGroupControl::UIGroupControl(GameObject* owner, int order):
	Component(owner,order)
{
	UISystem::Register(this);
}

UIGroupControl::~UIGroupControl()
{
	UISystem::Quit(this);
}
