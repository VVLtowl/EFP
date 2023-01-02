#pragma once
#include "Player.h"

class Character
{
public:
	Player* TargetPlayer;
public:
	virtual void InitPlayer() = 0;
};
