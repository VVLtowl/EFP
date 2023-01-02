#pragma once
#include "JudgementBehaviour.h"
#include <list>

class JBH_GameStart :
	public JudgementBehaviour
{
private:
	std::list<Player*>::iterator m_PlayerEnd;
	std::list<Player*>::iterator m_PlayerIterator;

public:
	void Start()override;
	void MainUpdate()override;
	void End()override;
	int ID() override { return BHID_STEP_GAME_START; };
};