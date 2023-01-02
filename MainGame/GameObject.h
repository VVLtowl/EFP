#pragma once
#include <vector>
#include <typeinfo>
#include <list>


class GameObject
{
public:
	enum State
	{
		ACTIVE,
		PAUSED,
		DEAD
	};
protected:
	// @brief	���������̃R���|�l���g����ĂɊǗ����邽��
	std::vector<class Component*> m_Components;
	std::list<Component*> m_PendingComponents;
	std::list<Component*> m_DeadComponents;
	bool m_NowUpdateComponent;

	// @brief	�Ώۂ̏��
	State m_State;

	// @brief	��ԓI�ϊ�
	class Transform3D* m_Transform3D;

private:
	void UpdateComponents();
	virtual void UpdateGameObject() = 0;

public:
	/*********************************************************
	* @brief	�������鎞�A�Q�[���Ώۂ��}�l�[�W���[�ɓo�^
	*			�폜���鎞�A�Q�[���Ώۂ��}�l�[�W���[���珜�O
	********************************************************/
	GameObject();
	virtual ~GameObject();

	// @brief	�Q�[���Ώۂ̍X�V
	void Update();

	/*********************************************************
	* @brief	�p����ŃR���|�l���g��ǉ����A
	*			�Q�[���I�u�W�F�N�g��g�ݗ��Ă�
	********************************************************/
	// @brief	�R���|�l���g�ǉ��ƍ폜
	void AddComponent(class Component* cpn);
	void RemoveComponent(class Component* cpn);
	// @bried	��̂̃R���|�l���g���擾
	template<typename ComponentType>
	ComponentType* GetComponent();

	// @brief	��Ԃ̐ݒ�Ǝ擾
	void SetState(State state) { m_State = state; }
	State GetState() const { return m_State; }

	// @brief	��ԓI�ϊ��̎擾
	Transform3D* GetTransform() { return m_Transform3D; };
};

//template<typename ComponentType>
//inline void GameObject::AddComponent<ComponentType>(Component* addCpn)
//{
//	// check this type component is only one in gameobject
//	ComponentType* sameCpn = GetComponent<ComponentType>();
//	if (sameCpn != nullptr)
//	{
//		delete sameCpn;
//	}
//
//	// Find the insertion point in the sorted vector
//	// (The first element with a order higher than me)
//	int addCpnOrder = addCpn->GetUpdateOrder();
//	auto iter = m_Components.begin();
//	while (iter != m_Components.end())
//	{
//		if (addCpnOrder < (*iter)->GetUpdateOrder())
//		{
//			break;
//		}
//		iter++;
//	}
//
//	// Inserts element before position of iterator
//	m_Components.insert(iter, addCpn);
//}

template<typename ComponentType>
inline ComponentType* GameObject::GetComponent()
{
	for (auto cpn : m_Components)
	{
		if (typeid(*cpn) == typeid(ComponentType))
		{
			return (ComponentType*)cpn;
		}
	}
}