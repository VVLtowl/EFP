#pragma once
#include "GameObject.h"
#include <list>

/*********************************************************
* @brief	ゲームオブジェクト　ヘッダー
********************************************************/
#include "Pawn_Normal.h"
#include "SquareObject.h"

#include "MainCamera.h"
#include "MainLight.h"

#include "DepthUI.h"
#include "Emitter.h"
#include "EffectParticle.h"
#include "ParticleSystem.h"

#include "Torus.h"
#include "Plane.h"
#include "Cube.h"

#include "UIPanel.h"
#include "ActSelection.h"

#include "LineCollisionTester.h"

//singleton
#include "LinePainter.h"


class GameObjectManager
{
private:
	// @brief	ゲーム対象を一斉に管理するリスト
	static std::list<GameObject*> m_GameObjects;
	// @brief	管理リストへ追加を待ってる対象を一時保留用リスト
	static std::list<GameObject*> m_PendingGameObjects;

	// @brief	対象更新中であるか
	// @details	対象更新している間、リスト要素の挿入と削除を行わない
	static bool m_NowUpdateGameObject;

public:
	template <typename GameObjectType>
	static GameObjectType* Create();

	static void Update();
	static void Clear();

	static void Register(GameObject* gameObj);
	static void Quit(GameObject* gameObj);
};

template<typename GameObjectType>
inline GameObjectType* GameObjectManager::Create()
{
	GameObjectType* obj = new GameObjectType();
	return obj;
}




