#pragma once
#include "Entity.h"
#include "NewbieGameObject.h"
#include "NewbieLayer.h"
#include "NewbieEnums.h"

namespace newbie
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObject, const eLayerType type);
		
	private:
		void CreateLayers();

	private:
		std::vector<Layer*> mLayers;
	};
}

