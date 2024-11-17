#include "NewbieTitleScene.h"
#include "NewbieInput.h"
#include "NewbiePlayScene.h"
#include "NewbieSceneManager.h"

namespace newbie
{
	TitleScene::TitleScene()
	{

	}

	TitleScene::~TitleScene()
	{

	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		// N키를 누르면 다음 화면으로 넘어가게끔
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		// Title Scene 렌더시 메시지 출력
		wchar_t str[50] = L"Title Scene";
		TextOut(hdc, 0, 0, str, 11);
	}
}