#include "main.h"
#include "ABH_PieceInit.h"

void ABH_PieceInit::Start()
{
	Pawn_Normal* piece = GameObjectManager::Create<Pawn_Normal>();
	piece->GetTransform()->SetPosition(StartPosition);
	TargetPiece->TargetPieceObject = piece;
}

void ABH_PieceInit::MainUpdate()
{
	if (CountDown >= 1)
	{
		D3DXVECTOR3 nowPos = TargetPiece->TargetPieceObject->GetTransform()->GetPosition();
		D3DXVECTOR3 move = (EndPosition - nowPos) / CountDown;
		nowPos = nowPos + move;
		TargetPiece->TargetPieceObject->GetTransform()->SetPosition(nowPos);

		CountDown--;
		return;
	}

	NextState();
}

void ABH_PieceInit::End()
{
	delete this;
}
