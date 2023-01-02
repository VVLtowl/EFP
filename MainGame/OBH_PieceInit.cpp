#include "main.h"
#include "TransformAnime.h"
#include "Piece.h"
#include "OBH_PieceInit.h"

void OBH_PieceInit::Start()
{
	TransformAnimeDescripition desc(StartPosition, EndPosition);
	desc.LoopCount = 1;
	desc.Duration = 40;
	desc.EndEvent = [this]()
	{
		IsOver = true;
	};
	TransformAnime* ani = new TransformAnime(TargetPiece->OwnPieceObject, desc);
}

void OBH_PieceInit::MainUpdate()
{
#if 0
	if (CountDown >= 1)
	{
		D3DXVECTOR3 nowPos = TargetPiece->OwnPieceObject->GetTransform()->GetPosition();
		D3DXVECTOR3 move = (EndPosition - nowPos) / CountDown;
		nowPos = nowPos + move;
		TargetPiece->OwnPieceObject->GetTransform()->SetPosition(nowPos);

		CountDown--;
	}
	else
	{
		NextState();
	}
#else 
	if (IsOver == true)
	{
		NextState();
	}
#endif
}

void OBH_PieceInit::End()
{
	delete this;
}
