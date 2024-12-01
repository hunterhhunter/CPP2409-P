#pragma once
#include "NewbieComponent.h"
#include "NewbieGameObject.h"
#include "NewbieLayer.h"
#include "NewbieScene.h"
#include "NewbieSceneManager.h"
#include "NewbieTransform.h"

namespace newbie
{
	namespace object
	{
		template <typename T>
		static T* Instantiate(newbie::enums::eLayerType type)
		{
			T* gameObject = new T();
			Scene* activeScene = SceneManager::GetActiveScene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			return gameObject;
		}

		template <typename T>
		static T* Instantiate(newbie::enums::eLayerType type, math::Vector2 position)
		{
			T* gameObject = new T();
			Scene* activeScene = SceneManager::GetActiveScene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			Transform* tr = gameObject->GetComponent<Transform>();
			tr->SetPosition(position);

			return gameObject;
		}

		static void Destroy(GameObject* gameObject)
		{
			if (gameObject == nullptr)
				return;
			gameObject->Death();
		}
	}
}