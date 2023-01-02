#pragma once
#include "Behaviour.h"
#include "Piece.h"

class ABH_PieceInit:
	public Behaviour
{
public:
	Piece* TargetPiece;
	D3DXVECTOR3 StartPosition;
	D3DXVECTOR3 EndPosition;
	float CountDown;
public:
	void Start()override;
	void MainUpdate()override;
	void End()override;
	int ID() override { return BHID_ANIME_PIECE_INIT; };
};

