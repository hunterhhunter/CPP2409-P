#pragma once
#include "NewbieSceneManager.h"
#include "NewbiePlayScene.h"

namespace newbie
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}