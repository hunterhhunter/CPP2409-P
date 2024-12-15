#include "NewbieSceneManager.h"
#include "NewbieDontDestroyOnLoad.h"

namespace newbie
{
	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		// 현재 씬 탈출
		if (mActiveScene)
			mActiveScene->OnExit();

		// 씬 찾기
		std::map<std::wstring, Scene*>::iterator iter = mScene.find(name);

		// ã�� Scene�� ���� �� nullptr ��ȯ
		if (iter == mScene.end())
			return nullptr;

		// �˻��� ���� ���� Ȱ��ȭ�� ������ ����
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		// Ȱ��ȭ�� �� ��ü�� ��ȯ
		return iter->second;
	}

	std::vector<GameObject*> SceneManager::GetGameObjects(eLayerType layer)
	{
		std::vector<GameObject*> gameObjects
			= mActiveScene->GetLayer(layer)->GetGameObjects();
		std::vector<GameObject*> dontDestroyOnLoad
			= mDontDestroyOnLoad->GetLayer(layer)->GetGameObjects();
		gameObjects.insert(gameObjects.end()
			, dontDestroyOnLoad.begin(), dontDestroyOnLoad.end());
		return gameObjects;
	}

	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();

	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
		mDontDestroyOnLoad->Render(hdc);

	}

	void SceneManager::Release()
	{
		// 각 씬들 메모리에서 제거
		for (auto& iter : mScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		mDontDestroyOnLoad->Destroy();
	}
}
