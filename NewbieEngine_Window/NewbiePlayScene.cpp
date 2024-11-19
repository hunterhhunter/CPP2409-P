#include "NewbiePlayScene.h"
#include "NewbieGameObject.h"
#include "NewbiePlayer.h"
#include "NewbieTransform.h"
#include "NewbieSpriteRenderer.h"
#include "NewbieInput.h"
#include "NewbieTitleScene.h"
#include "NewbieSceneManager.h"
#include "NewbieObject.h"
#include "NewbieBackGround.h"

namespace newbie
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		// BackGround 유닛 추가
		{
			bg = object::Instantiate<BackGround>(newbie::enums::eLayerType::BackGround, Vector2(0, 0));
			SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			sr->ImageLoad(L"C:\\Users\\slugg\\Documents\\GitHub\\CPP2409-P\\Resources\\BackGroundImage.png");
			
			player = object::Instantiate<Player>(newbie::enums::eLayerType::Player, Vector2(0, 0));
			SpriteRenderer* sr2 = player->AddComponent<SpriteRenderer>();
			sr2->ImageLoad(L"C:\\Users\\slugg\\Documents\\GitHub\\CPP2409-P\\Resources\\cha.png");
			

			// 게임 오브젝트 생성 후 레이어와 게임 오브젝트 init
			Scene::Initialize();
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t str[50] = L"Play Scene";
		TextOut(hdc, 0, 0, str, 10);
	}

	void PlayScene::OnEnter()
	{

	}

	void PlayScene::OnExit()
	{
		/*Transform* tr = bg->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, 0));*/
	}
}