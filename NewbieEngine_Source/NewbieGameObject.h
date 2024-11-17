#pragma once
#include "Commoninclude.h"
#include "NewbieComponent.h"

namespace newbie
{
	// Actor
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Setowner(this);
			mComponents.push_back(comp);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* comonent = nullptr;
			for (Component* comp : mComponents)
			{
				// dynamic_cast는 캐스팅 가능시 캐스트 된 결과를, 불가능시 nullptr 반환
				component = dynamic_cast<T*>(comp);
				if (component)
					break;
			}
			return component;
		}

	private:
		std::vector<Component*> mComponents;
	};
}