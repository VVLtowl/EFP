#pragma once
#include <vector>
#include <list>
#include "Excuter.h"
#include "Player.h"

#pragma region ========== loop list ==========

template <typename T>
class LoopList
{
public:

private:
	std::list<T> m_List;
	typename std::list<T>::iterator m_Iterator;

public:
	void Add(T t) { m_List.push_back(t); };
	T& First();
	T& Next();
};

template<typename T>
inline T& LoopList<T>::First()
{
	m_Iterator = m_List.begin();
	return (*m_Iterator);
}


template<typename T>
inline T& LoopList<T>::Next()
{
	m_Iterator++;

	if (m_Iterator == m_List.end())
	{
		m_Iterator = m_List.begin();
	}

	return (*m_Iterator);
}

#pragma endregion


class Judgement
{
public:
	enum StepID
	{
		STEP_GAME_START,
		STEP_RPS,
		STEP_BAD_ACT,
		STEP_GOOD_ACT,
		STEP_TURN_END,
	};

	/*********************************************************
	* @brief	ジャッジメント行為
	* @details	固定行為(メインゲームループ)、特殊追加行為
	********************************************************/
private:
	std::vector<Behaviour*> m_MainLoopBehaviours;
	std::list<Behaviour*> m_SpecialBehaviours;

	/*********************************************************
	* @brief	プレイヤー行動グループ
	********************************************************/
public:
	LoopList<Player*> BadActGroup;
	LoopList<Player*> GoodActGroup;

public:
	void Init();
	void Start();
};