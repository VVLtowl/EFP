#pragma once
#include "GameObject.h"
#include <list>

/*********************************************************
* @brief	�Q�[���I�u�W�F�N�g�@�w�b�_�[
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
	// @brief	�Q�[���Ώۂ���ĂɊǗ����郊�X�g
	static std::list<GameObject*> m_GameObjects;
	// @brief	�Ǘ����X�g�֒ǉ���҂��Ă�Ώۂ��ꎞ�ۗ��p���X�g
	static std::list<GameObject*> m_PendingGameObjects;

	// @brief	�ΏۍX�V���ł��邩
	// @details	�ΏۍX�V���Ă���ԁA���X�g�v�f�̑}���ƍ폜���s��Ȃ�
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




