#pragma once
#include <list>
#include "Singleton.h"
#include "GameManager.h"

#include "JBH_GameStart.h"
#include "ABH_PieceInit.h"

class BehaviourFactory: 
	public Singleton<BehaviourFactory>
{
public:
	std::list<Behaviour*> Behaviours;

public:
	template <typename ConstractBehaviourType>
	ConstractBehaviourType* CreateEternalBH();

	template <typename ConstractBehaviourType>
	ConstractBehaviourType* CreateOnceBH();
};

template <typename ConstractBehaviourType>
inline ConstractBehaviourType* BehaviourFactory::CreateEternalBH()
{
	ConstractBehaviourType* bh = new ConstractBehaviourType();
	Behaviours.push_back(bh);
	bh->SetExcuter(GameManager::Instance());

	return bh;
}

template <typename ConstractBehaviourType>
inline ConstractBehaviourType* BehaviourFactory::CreateOnceBH()
{
	ConstractBehaviourType* bh = new ConstractBehaviourType();
	bh->SetExcuter(GameManager::Instance());

	return bh;
}