#pragma once
#include "Component.h"
#include <list>

class UIGroupControl :
	public Component
{
public:
	UIGroupControl(
		class GameObject* owner,
		int order=COMP_COUNT
	);
	virtual ~UIGroupControl();
	virtual void Update()override = 0;
};

