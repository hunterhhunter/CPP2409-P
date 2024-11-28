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
#include "NewbieTexture.h"
#include "NewbieResources.h"
#include "NewbiePlayerScript.h"
#include "NewbieCamera.h"
#include "NewbieRenderer.h"
#include "NewbieAnimator.h"
#include "NewbieCat.h"
#include "NewbieCatScript.h"

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
		// main Camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;

		// Make Player
		mPlayer = object::Instantiate<Player>(enums::eLayerType::Particle);
		/*SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
		sr->SetSize(Vector2(3.0f, 3.0f));*/
		mPlayer->AddComponent<PlayerScript>();

		// Set Player Texture
		graphics::Texture* packmanTexture = Resources::Find<graphics::Texture>(L"Cat");

		//// Add Player Animation
		Animator* animator = mPlayer->AddComponent<Animator>();
		/*animator->CreateAnimation(L"CatFrontMove", packmanTexture
			, Vector2(222.0f, 222.0f), Vector2(386.0f, 246.0f), Vector2::Zero, 8, 0.1f);*/
		/*animator->PlayAnimation(L"CatFrontMove", true);*/

		animator->CreateAnimation(L"DownWalk", packmanTexture
			, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f)
			, Vector2::Zero, 4, 0.1f);
		animator->CreateAnimation(L"RightWalk", packmanTexture
			, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f)
			, Vector2::Zero, 4, 0.1f);
		animator->CreateAnimation(L"UpWalk", packmanTexture
			, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f)
			, Vector2::Zero, 4, 0.1f);
		animator->CreateAnimation(L"LeftWalk", packmanTexture
			, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f)
			, Vector2::Zero, 4, 0.1f);
		animator->CreateAnimation(L"SitDown", packmanTexture
			, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f)
			, Vector2::Zero, 4, 0.1f);
		animator->CreateAnimation(L"Grooming", packmanTexture
			, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f)
			, Vector2::Zero, 4, 0.1f);

		animator->PlayAnimation(L"SitDown", false);

		 mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 100.0f));
		 mPlayer->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
		

		//// Make BackGround
		//GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::Player);
		//SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
		//bgSr->SetSize(Vector2(1.1f, 1.1f));

		//// BackGround Texture
		//graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Bubble");
		//bgSr->SetTexture(bgTexture);

		 // make Cat
		 Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Player);
		 cat->AddComponent<CatScript>();

		 graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		 Animator* catAnimator = cat->AddComponent<Animator>();
		 catAnimator->CreateAnimation(L"DownWalk", catTex
			 , Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		 catAnimator->CreateAnimation(L"RightWalk", catTex
			 , Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		 catAnimator->CreateAnimation(L"UpWalk", catTex
			 , Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		 catAnimator->CreateAnimation(L"LeftWalk", catTex
			 , Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		 catAnimator->CreateAnimation(L"SitDown", catTex
			 , Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		 catAnimator->CreateAnimation(L"Grooming", catTex
			 , Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		 catAnimator->CreateAnimation(L"LayDown", catTex
			 , Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

		 catAnimator->PlayAnimation(L"SitDown", false);
		 cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
		 cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

		Scene::Initialize();
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