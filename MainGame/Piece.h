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
	* @brief	�R�}�̑���
	********************************************************/
public:
	class Square* FootOnSquare;

	//State
	//State State;

	//�w�c
	int Camp;

	//�g���W�����
	bool IsOpenStatus = false;

	//�Q�[���I�u�W�F�N�g
	class PieceObject* OwnPieceObject;

	/*********************************************************
	* @brief	�R�}�̍s��
	********************************************************/
public:
};