#include "main.h"
#include "StateFactory.h"
#include "Board.h"

void Board::Init()
{
	int squareType[SQUARE_Z_NUM][SQUARE_X_NUM] =
	{
		{0,0,9,0,0,},
		{0,0,1,1,0,},
		{0,0,0,0,0,},
		{0,0,2,0,2,},
		{0,2,0,2,0,},
	};
	Square* squareMatrix[SQUARE_Z_NUM][SQUARE_X_NUM];
	//create all square
	{
		float deltaX = SQUARE_SIZE;
		float posX0 = (SQUARE_X_NUM / 2.0f * (-1.0f) + 0.5f) * deltaX;
		float deltaZ = SQUARE_SIZE;
		float posZ0 = (SQUARE_Z_NUM / 2.0f * (-1.0f) + 0.5f) * deltaZ;
		float posY0 = -0.1f;// +((float)(rand() % 100) / 100.0f - 0.5f) * 2 * 2.0f;
		for (int z = 0; z < SQUARE_Z_NUM; z++)
		{
			for (int x = 0; x < SQUARE_X_NUM; x++)
			{
				Square* sq = new Square();
				Squares.push_back(sq);
				squareMatrix[z][x] = sq;

				SquareObject* sqObj= GameObjectManager::Create<SquareObject>();
				sq->TargetSquareObject = sqObj;
				float posX = posX0 + x * deltaX;
				float posZ = posZ0 + z * deltaZ;
				float posY= posY = posY0 +((float)(rand() % 100) / 100.0f - 0.5f) * 2 * 0.1f;
				sqObj->GetTransform()->SetPosition(posX, posY, posZ);

				switch (squareType[z][x])
				{
				
				case 9://set goal
				{
					StateFactory::Instance()->Create<SquareState_Goal>(sq);
				}
				break;
				
				case 1://set to good start square
				{
					GoodStartSquare.push_back(sq);
				}
				break;

				case 2://set to bad start square
				{
					BadStartSquare.push_back(sq);
				}
				break;

				}
			}
		}
	}

	//connect square
	{
		for (int z = 0; z < SQUARE_Z_NUM; z++)
		{
			for (int x = 0; x < SQUARE_X_NUM; x++)
			{
				Square* sq = squareMatrix[z][x];
				Square* sqUp = nullptr;
				Square* sqRight = nullptr;
				Square* sqDown = nullptr;
				Square* sqLeft = nullptr;

				//axis x
				if (x > 0)
				{
					sqLeft = squareMatrix[z][x - 1];
				}
				if (x < SQUARE_X_NUM - 1)
				{
					sqRight = squareMatrix[z][x + 1];
				}

				//axis z
				if (z > 0)
				{
					sqDown = squareMatrix[z - 1][x];
				}
				if (z < SQUARE_Z_NUM - 1)
				{
					sqUp = squareMatrix[z + 1][x];
				}

				sq->Neighbors[DIR_UP] = sqUp;
				sq->Neighbors[DIR_RIGHT] = sqRight;
				sq->Neighbors[DIR_DOWN] = sqDown;
				sq->Neighbors[DIR_LEFT] = sqLeft;
			}
		}
	}
}

void Board::Clear()
{
	for (auto sq : Squares)
	{
		delete sq;
	}
	Squares.clear();
}

Square* Board::GetBadStartSquare()
{
	Square* square=nullptr;
	for (auto sq : BadStartSquare)
	{
		if (sq->Piece == nullptr)
		{
			square = sq;
			break;
		}
	}
	return square;
}

Square* Board::GetGoodStartSquare()
{
	Square* square = nullptr;
	for (auto sq : GoodStartSquare)
	{
		if (sq->Piece == nullptr)
		{
			square = sq;
			break;
		}
	}
	return square;
}
