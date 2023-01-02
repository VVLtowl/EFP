#include "main.h"
#include "Transform3D.h"
#include "BehaviourFactory.h"
#include "GameManager.h"
#include "JBH_GameStart.h"

void JBH_GameStart::Start()
{
	m_PlayerEnd = GameManager::Instance()->Players.end();
	m_PlayerIterator = GameManager::Instance()->Players.begin();
}

void JBH_GameStart::MainUpdate()
{
	if (m_PlayerIterator != m_PlayerEnd)
	{
		Player* player = (*m_PlayerIterator);
		Piece* piece = &player->Piece;
		Square* startSquare = piece->Camp == CAMP_BAD ?
			GameManager::Instance()->MainBoard->GetBadStartSquare() :
			GameManager::Instance()->MainBoard->GetGoodStartSquare();

		//test need piece in square event
		piece->FootOnSquare.emplace_back(startSquare);
		startSquare->Piece = piece;
		D3DXVECTOR3 startSquarePos = startSquare->TargetSquareObject->GetTransform()->GetPosition();

		ABH_PieceInit* pieceInit = 
			BehaviourFactory::Instance()->CreateOnceBH<ABH_PieceInit>();
		pieceInit->TargetPiece = piece;
		pieceInit->StartPosition = startSquarePos + D3DXVECTOR3(0, 10, 0);
		pieceInit->EndPosition = startSquarePos;
		pieceInit->CountDown = 15;
		GameManager::Instance()->JumpTo(pieceInit);

		m_PlayerIterator++;
		return;
	}

	NextState();
}

void JBH_GameStart::End()
{
	delete this;
}
