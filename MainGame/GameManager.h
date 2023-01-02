#pragma once
#include "Singleton.h"
#include "GameState.h"
#include "Excuter.h"

#include "Player.h"
#include "Judgement.h"
#include "Board.h"
#include <list>


/*********************************************************
* @brief	�Q�[���ݒ�
********************************************************/
const int PLAYER_MAX = 6;
const int PLAYER_BAD_START_NUM = 4;
const int PLAYER_GOOD_START_NUM = 2;

/*********************************************************
* @brief	���C���Q�[���̎��s���Ǘ�����
********************************************************/
class GameManager:
	public Singleton<GameManager>,
	public Excuter
{
public:
	void Start();
	void Update();
	void End();

public:
	std::list<Player*> Players;
	Judgement MainJudge;
	Board MainBoard;
};

