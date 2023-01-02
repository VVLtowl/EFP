#pragma once
#include "GameObject.h"

const D3DXVECTOR2 ACTSELECTION_IDLE_SIZE = { 1.5f,1.5f };
const float ACTSELECTION_HIGHLIGHT_SCALE = 1.2f;
const D3DXVECTOR3 ACTSELECTION_HIGHLIGHT_MOVE = { 0,0,0 };

class ActSelection :
    public GameObject
{
	/*********************************************************
	* @brief	gameobject interface override
	********************************************************/
public:
	ActSelection(const D3DXVECTOR3& pos = V3_ZERO, const  D3DXVECTOR3& scl = V3_ONE);
	~ActSelection();
	void UpdateGameObject()override;

	/*********************************************************
	* @brief	コンポネント
	********************************************************/
private:
	class Polygon2D* m_Polygon2D;
	class BoxCollider* m_BoxCollider;
	class Button* m_Button;
	class LookAtCamera* m_LookAtCamera;
	class DrawLine* m_DrawLine;

	/*********************************************************
	* @brief	customize
	********************************************************/
private:
	D3DXVECTOR3 m_OriginalPosition;
	D3DXVECTOR3 m_OriginalScale;
	class GameObject* m_Hint;
};

