#include "NewbieScene.h"

namespace newbie
{
	Scene::Scene()
		: mGameObjects{}
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		// 게임 오브젝트들 업데이트
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render(hdc);
		}
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}