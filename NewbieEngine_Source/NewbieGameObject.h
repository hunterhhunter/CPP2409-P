#pragma once
#include "Commoninclude.h"
#include "NewbieComponent.h"

//namespace newbie
//{
//	namespace object
//	{
//		void Destroy(GameObject* gameObject);
//	}
//}

namespace newbie
{
	// Actor
	class GameObject
	{
	public:
		//friend void object::Destroy(GameObject* obj);

		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		// 가변형으로 다형성 구현 -> GameObject를 상속받은 모든 객체는 이 함수 사용 가능
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Initialize();
			comp->SetOwner(this);
			mComponents[(UINT)comp->GetType()] = comp;

			return comp;
		}

		// 가변형으로 다형성 구현
		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				// dynamic_cast는 캐스팅 가능시 캐스트 된 결과를, 불가능시 nullptr 반환
				component = dynamic_cast<T*>(comp);
				if (component)
					break;
			}
			return component;
		}

		eState GetState() { return mState; }
		void SetActive(bool power)
		{
			if (power == true)
				mState = eState::Active;
			if (power == false)
				mState = eState::Paused;
		}
		bool IsActive() { return mState == eState::Active; }
		void Death() { mState = eState::Dead; }

		bool IsDead() { return mState == eState::Dead; }

	private:
		void initializeTransform();
		void death() { mState = eState::Dead; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}