#include "main.h"
#include "GameManager.h"

void GameManager::Start()
{
	//test
	{
		//create judgement
		MainJudge.Init();

		//create board
		MainBoard.Init();


		//create player
		//test input player info
		{
			//create bad man
			int playerCount = 0;
			for (int i = 0; i < PLAYER_BAD_START_NUM; i++)
			{
				playerCount++;
				Player* player = new Player();
				Pawn_Normal* normalPawn = GameObjectManager::Create<Pawn_Normal>();
				normalPawn->GetTransform()->SetPosition(i + 1, 1000, 0);

				player->OwnPiece.Camp = CAMP_BAD;
				player->OwnPiece.IsOpenStatus = false;
				player->OwnPiece.OwnPieceObject = normalPawn;
				player->Name = "BAD-" + std::to_string(playerCount);
				Players.emplace_back(player);
			}
			//create good man
			playerCount = 0;
			for (int i = 0; i < PLAYER_GOOD_START_NUM; i++)
			{
				playerCount++;
				Player* player = new Player();
				Pawn_Normal* normalPawn = GameObjectManager::Create<Pawn_Normal>();
				normalPawn->GetTransform()->SetPosition(-i, 1000, 0);

				player->OwnPiece.Camp = CAMP_GOOD;
				player->OwnPiece.IsOpenStatus = false;
				player->OwnPiece.OwnPieceObject = normalPawn;
				player->Name = "GOOD-" + std::to_string(playerCount);
				Players.emplace_back(player);
			}
		}
		
		

		//set up act group
		for (auto player : Players)
		{
			if (player->OwnPiece.Camp == CAMP_BAD)
			{
				MainJudge.BadActGroup.Add(player);
			}
			else if (player->OwnPiece.Camp == CAMP_GOOD)
			{
				MainJudge.GoodActGroup.Add(player);
			}
		}
	}


	//start
	MainJudge.Start();
}

void GameManager::Update()
{
	Excute();
}

void GameManager::End()
{
	//delete player
	for (auto p : Players)
	{
		delete p;
	}
}
