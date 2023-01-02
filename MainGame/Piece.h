#pragma once
#include <list>


class Square;
class PieceObject;

enum CampType
{
	CAMP_NONE,
	CAMP_BAD,
	CAMP_GOOD,
};

class Piece
{
public:
	std::list<Square*> FootOnSquare;

	//State
	//State State;

	//Status
	int Camp;
	bool IsOpenStatus = false;

	PieceObject* TargetPieceObject;
};