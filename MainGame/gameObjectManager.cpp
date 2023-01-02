#include "main.h"
#include "gameObjectManager.h"

std::list<GameObject*> GameObjectManager::m_GameObjects;
std::list<GameObject*> GameObjectManager::m_PendingGameObjects;
bool GameObjectManager::m_NowUpdateGameObject;

void GameObjectManager::Register(GameObject* gameObj)
{
	//m_GameObjects�̓��C���X�V���������Ă���ԁA
	//�v�f�̑}����m_PendingGameObjects�Ɉꎞ�ۗ�
	if (m_NowUpdateGameObject)
	{
		m_PendingGameObjects.emplace_back(gameObj);
	}
	else
	{
		for (auto obj : m_GameObjects)
		{
			if (obj == gameObj)
			{
				return;
			}
		}
		m_GameObjects.emplace_back(gameObj);
	}
}

void GameObjectManager::Quit(GameObject* gameObj)
{
	m_GameObjects.remove(gameObj);
}

void GameObjectManager::Update()
{
	//�Ǘ����X�g����폜��҂��Ă�Ώۂ��ꎞ�ۗ��p���X�g
	std::list<GameObject*> m_DeadGameObjects;

	//update gameObjects
	m_NowUpdateGameObject = true;
	for (auto obj : m_GameObjects)
	{
		obj->Update();
		if (obj->GetState() == GameObject::DEAD)
		{
			m_DeadGameObjects.emplace_back(obj);
		}
	}
	m_NowUpdateGameObject = false;

	//�ۗ����̑ΏۑS�����C�����X�g�֒ǉ�
	for (auto pending : m_PendingGameObjects)
	{
		Register(pending);
	}
	m_PendingGameObjects.clear();

	//delete dead actors
	for (auto obj : m_DeadGameObjects)
	{
		delete obj;
	}
}

void GameObjectManager::Clear()
{
	while (m_GameObjects.empty() == false)
	{
		delete m_GameObjects.back();
	}
}
