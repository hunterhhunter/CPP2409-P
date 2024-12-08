#pragma once
#include "NewbieSceneManager.h"
#include "NewbiePlayScene.h"
#include "NewbieTitleScene.h"
#include "NewbieToolScene.h"

namespace newbie
{
	void LoadScenes()
	{
		// SceneManager::CreateScene<TitleScene>(L"TitleScene");
		// SceneManager::CreateScene<PlayScene>(L"PlayScene");
		// SceneManager::LoadScene(L"PlayScene");

		SceneManager::CreateScene<ToolScene>(L"ToolScene");
		SceneManager::LoadScene(L"ToolScene");
	}
}