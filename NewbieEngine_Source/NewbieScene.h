#pragma once
#include "Entity.h"
#include "NewbieGameObject.h"

namespace newbie
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void AddGameObject(GameObject* gameObject);
		
	private:
		std::vector<GameObject*> mGameObjects;
	};
}

