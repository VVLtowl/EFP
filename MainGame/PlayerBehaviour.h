#pragma once
#include "Player.h"
#include "Behaviour.h"

class PlayerBehaviour :public Behaviour
{
protected:
	Player* m_Player;
public:
	void SetPlayer(Player* player);
};