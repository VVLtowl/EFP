#pragma once
#include <list>
#include <string>
#include "Piece.h"

class Player
{
public:
	Player();
	~Player();

public:
	enum FixedBHID
	{
		INPUT_HAND,
		SELECT_ACT,

		CLEAR_POINT,
		//UPDATE_STATE,

		FIXED_BHID_MAX,
	};

	/*********************************************************
	* @brief	�v���C���[�s��
	* @details	�Œ�s�ׁA�s���s�ׁA����ǉ��s��
	********************************************************/
private:
	Behaviour* m_FixedBehaviours[FIXED_BHID_MAX];
	std::list<Behaviour*> m_ActionBehaviours;
	std::list<Behaviour*> m_SpecialBehaviours;

public:
	void SetFixedBehaviour(FixedBHID id, Behaviour* bh) { m_FixedBehaviours[id] = bh; };
	void AddActBehaviour(Behaviour* bh) { m_ActionBehaviours.push_back(bh); };
	Behaviour* GetFixedBehaviour(FixedBHID id) { return m_FixedBehaviours[id]; };
	std::list<Behaviour*>* GetActBehaviourList() { return &m_ActionBehaviours; };

	/*********************************************************
	* @brief	�v���C���[����
	********************************************************/
public:
	//Name
	std::string Name;

	//Hand
	std::list<int> Hands;

	//ActPoint
	int ActPoint = 0;

	//Piece
	Piece OwnPiece;
};

