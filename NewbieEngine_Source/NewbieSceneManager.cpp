#include "NewbieSceneManager.h"

namespace newbie
{
	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		// mActiveScene이 존재할 때
		if (mActiveScene)
			mActiveScene->OnExit();

		// Scene을 검색
		std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);

		// 찾는 Scene이 없을 때 nullptr 반환
		if (iter == mScene.end())
			return nullptr;

		// 검색된 씬을 현재 활성화된 씬으로 설정
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		// 활성화된 씬 객체를 반환
		return iter->second;
	}

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
}
