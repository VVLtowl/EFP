#pragma once
#include "GameObject.h"

class Plane:
	public GameObject
{
	/*********************************************************
	* @brief	gameobject interface override
	********************************************************/
public:
	Plane();
	void UpdateGameObject()override;

	/*********************************************************
	* @brief	コンポネント
	********************************************************/
private:
	class Polygon2D* m_Polygon2D;

	/*********************************************************
	* @brief	customize
	********************************************************/
};

