#pragma once
#include "Entity.h"
#include "CommonInclude.h"
#include "NewbieGameObject.h"

namespace newbie
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameObject);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}

