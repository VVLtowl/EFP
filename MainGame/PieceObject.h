#pragma once
#include "GameObject.h"

class PieceObject :
    public GameObject
{
	/*********************************************************
	* @brief	gameobject interface override
	********************************************************/
public:
	PieceObject();
	virtual ~PieceObject();
	virtual void UpdateGameObject()override = 0;

	/*********************************************************
	* @brief	�R���|�l���g
	********************************************************/
protected:
	class Polygon2D* m_Polygon2D;

	/*********************************************************
	* @brief	customize
	********************************************************/
};
