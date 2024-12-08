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
		// 하나의 게임 오브젝트 생성하는 템플릿
		// 현재 씬에 삽입됨
		template <typename T>
		static T* Instantiate(newbie::enums::eLayerType type)
		{
			T* gameObject = new T();
			gameObject->SetLayerType(type);
			Scene* activeScene = SceneManager::GetActiveScene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			return gameObject;
		}

		// 정적 Instantiate
		template <typename T>
		static T* Instantiate(newbie::enums::eLayerType type, math::Vector2 position)
		{
			T* gameObject = new T();
			gameObject->SetLayerType(type);
			Scene* activeScene = SceneManager::GetActiveScene();
			Layer* layer = activeScene->GetLayer(type);
			layer->AddGameObject(gameObject);

			Transform* tr = gameObject->GetComponent<Transform>();
			tr->SetPosition(position);

			return gameObject;
		}

		static void DontDestroyOnLoad(GameObject* gameObject)
		{
			Scene* activeScene = SceneManager::GetActiveScene();
			activeScene->EraseGameObject(gameObject);

			// 해당 게임 오브젝트를 DontDestroy씬으로 넣기
			Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
			dontDestroyOnLoad->AddGameObject(gameObject, gameObject->GetLayerType());
		}
	}
}