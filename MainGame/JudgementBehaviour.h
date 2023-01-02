#pragma once
#include "Judgement.h"
#include "Behaviour.h"

class JudgementBehaviour :
	public Behaviour
{
protected:
	Judgement* m_Judgement;

public:
	void SetJudgement(Judgement* jud) { m_Judgement = jud; };
};