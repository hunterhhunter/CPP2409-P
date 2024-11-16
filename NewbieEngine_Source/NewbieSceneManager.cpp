#include "NewbieSceneManager.h"

namespace newbie
{
	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mactiveScene = nullptr;

	void newbie::SceneManager::Initialize()
	{
	}

	void newbie::SceneManager::Update()
	{
		mactiveScene->Update();
	}

	void newbie::SceneManager::LateUpdate()
	{
		mactiveScene->LateUpdate();
	}

	void newbie::SceneManager::Render(HDC hdc)
	{
		mactiveScene->Render(hdc);
	}
}
