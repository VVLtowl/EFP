#include "main.h"
#include "BehaviourFactory.h"
#include "GameManager.h"
#include "Judgement.h"

void Judgement::Init()
{
	//set up judgement behaviour
	{
		m_MainLoopBehaviours.push_back(BehaviourFactory::CreateEternalBH<JBH_GameStart>());
	}
}

void Judgement::Start()
{
	GameManager::Instance()->SetExcute(
		m_MainLoopBehaviours[STEP_GAME_START]
	);
}