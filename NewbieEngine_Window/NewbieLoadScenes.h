#pragma once
#include "NewbieSceneManager.h"
#include "NewbiePlayScene.h"
#include "NewbieTitleScene.h"

namespace newbie
{
	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::LoadScene(L"PlayScene");
	}
}