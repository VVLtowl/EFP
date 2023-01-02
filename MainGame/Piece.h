#pragma once
#include <list>


enum PieceType
{
	PIECE_NORMAL,
};

enum CampType
{
	CAMP_NONE,
	CAMP_BAD,
	CAMP_GOOD,
};

class Piece
{
	/*********************************************************
	* @brief	コマの属性
	********************************************************/
public:
	class Square* FootOnSquare;

	//State
	//State State;

	//陣営
	int Camp;

	//身分展示状態
	bool IsOpenStatus = false;

	//ゲームオブジェクト
	class PieceObject* OwnPieceObject;

	/*********************************************************
	* @brief	コマの行為
	********************************************************/
public:
};