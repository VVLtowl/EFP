#pragma once
#include <list>
#include "Singleton.h"
#include "GameManager.h"

#include "JBH_GameStart.h"
#include "OBH_PieceInit.h"


class BehaviourFactory
{
public:
	static std::list<Behaviour*> Behaviours;

public:
	template <typename ConstractBehaviourType>
	static ConstractBehaviourType* CreateEternalBH();

	template <typename ConstractBehaviourType>
	static ConstractBehaviourType* CreateOnceBH();
};


template <typename ConstractBehaviourType>
inline ConstractBehaviourType* BehaviourFactory::CreateEternalBH()
{
	ConstractBehaviourType* bh = new ConstractBehaviourType();
	Behaviours.push_back(bh);

	//行動は全部ゲームマネジャーに実行される
	bh->SetExcuter(GameManager::Instance());

	return bh;
}

template <typename ConstractBehaviourType>
inline ConstractBehaviourType* BehaviourFactory::CreateOnceBH()
{
	ConstractBehaviourType* bh = new ConstractBehaviourType();

	//行動は全部ゲームマネジャーに実行される
	bh->SetExcuter(GameManager::Instance());

	return bh;
}