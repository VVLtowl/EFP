#pragma once
#include "Component.h"

class Transform:
	public Component
{
public:
	Transform(class GameObject* owner, int updateOrder = COMP_COUNT);//更新が一番遅く順
	virtual ~Transform();
	virtual void Update() override = 0;
};