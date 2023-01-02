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
	// @brief	自分所属のコンポネントを一斉に管理するため
	std::vector<class Component*> m_Components;
	std::list<Component*> m_PendingComponents;
	std::list<Component*> m_DeadComponents;
	bool m_NowUpdateComponent;

	// @brief	対象の状態
	State m_State;

	// @brief	空間的変換
	class Transform3D* m_Transform3D;

private:
	void UpdateComponents();
	virtual void UpdateGameObject() = 0;

public:
	/*********************************************************
	* @brief	生成する時、ゲーム対象をマネージャーに登録
	*			削除する時、ゲーム対象をマネージャーから除外
	********************************************************/
	GameObject();
	virtual ~GameObject();

	// @brief	ゲーム対象の更新
	void Update();

	/*********************************************************
	* @brief	継承先でコンポネントを追加し、
	*			ゲームオブジェクトを組み立てる
	********************************************************/
	// @brief	コンポネント追加と削除
	void AddComponent(class Component* cpn);
	void RemoveComponent(class Component* cpn);
	// @bried	具体のコンポネントを取得
	template<typename ComponentType>
	ComponentType* GetComponent();

	// @brief	状態の設定と取得
	void SetState(State state) { m_State = state; }
	State GetState() const { return m_State; }

	// @brief	空間的変換の取得
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