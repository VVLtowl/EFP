#pragma once
#include <list>
#include "Square.h"

#pragma region ========== definition ==========
const unsigned int SQUARE_X_NUM = 5;
const unsigned int SQUARE_Z_NUM = 5;
#pragma endregion

class Board
{
public:
	/*********************************************************
	* @brief	ƒ}ƒX‚ğˆêÄ‚ÉŠÇ—‚·‚é
	********************************************************/
	std::list<Square*> Squares;

public:
	void Init();
	void Clear();


public:
	std::list<Square*> BadStartSquare;
	std::list<Square*> GoodStartSquare;

public:
	Square* GetBadStartSquare();
	Square* GetGoodStartSquare();
};
