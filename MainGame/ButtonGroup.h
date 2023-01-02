#pragma once
#include "UIGroupControl.h"

class ButtonGroup :
    public UIGroupControl
{
public:
	ButtonGroup(class GameObject* owner);
	void Update()override;


public:
	void AddButton(class Button* btn);
private:
	std::list<class Button*> m_Buttons;
};

