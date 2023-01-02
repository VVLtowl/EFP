#include "main.h"
#include "GameManager.h"

void GameManager::Start()
{
	//test
	{
		//create judgement
		MainJudge = new Judgement();
		MainJudge->Init();

		//create board
		MainBoard = new Board();
		MainBoard->Init();

		//create player
		int playerCount = 0;
		for (int i = 0; i < PLAYER_BAD_START_NUM; i++)
		{
			playerCount++;
			Player* player = new Player();

			player->Piece.Camp = CAMP_BAD;
			player->Name = "BAD-" + std::to_string(playerCount);
			Players.push_back(player);
		}
		playerCount = 0;
		for (int i = 0; i < PLAYER_GOOD_START_NUM; i++)
		{
			playerCount++;
			Player* player = new Player();

			player->Piece.Camp = CAMP_GOOD;
			player->Name = "GOOD-" + std::to_string(playerCount);
			Players.push_back(player);
		}

		//set up act group
		for (auto player : Players)
		{
			if (player->Piece.Camp == CAMP_BAD)
			{
				MainJudge->BadActGroup.Add(player);
			}
			else if (player->Piece.Camp == CAMP_GOOD)
			{
				MainJudge->GoodActGroup.Add(player);
			}
		}
	}


	//start
	MainJudge->Start();
}

void GameManager::Update()
{
	Excute();
}

void GameManager::End()
{

}
