#include "NewbieSceneManager.h"

namespace newbie
{
	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		// mActiveScene�� ������ ��
		if (mActiveScene)
			mActiveScene->OnExit();

		// Scene�� �˻�
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

	void SceneManager::Release()
	{
		// 각 씬들 메모리에서 제거
		for (auto& iter : mScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}
