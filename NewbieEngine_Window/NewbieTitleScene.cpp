#include "NewbieTitleScene.h"
#include "NewbiePlayScene.h"
#include "NewbieGameObject.h"
#include "NewbiePlayer.h"
#include "NewbieTransform.h"
#include "NewbieSpriteRenderer.h"
#include "NewbieInput.h"
#include "NewbieTitleScene.h"
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

		/*Player* bg = new Player();
		Transform* tr = bg->AddComponent<Transform>();
		tr->SetPosition(Vector2(0, 0));
		tr->SetName(L"TR");

		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		sr->SetName(L"SR");
		sr->ImageLoad(L"C:\\Users\\slugg\\Documents\\GitHub\\CPP2409-P\\Resources\\BackGroundImage2.png");

		AddGameObject(bg, enums::eLayerType::BackGround);*/
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