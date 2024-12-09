#include "NewbiePlayScene.h"
#include "../NewbieEngine_Source/NewbieGameObject.h"
#include "NewbiePlayer.h"
#include "../NewbieEngine_Source/NewbieTransform.h"
#include "../NewbieEngine_Source/NewbieSpriteRenderer.h"
#include "../NewbieEngine_Source/NewbieInput.h"
#include "NewbieTitleScene.h"
#include "../NewbieEngine_Source/NewbieSceneManager.h"
#include "../NewbieEngine_Source/NewbieObject.h"
#include "NewbieBackGround.h"
#include "../NewbieEngine_Source/NewbieTexture.h"
#include "../NewbieEngine_Source/NewbieResources.h"
#include "NewbiePlayerScript.h"
#include "../NewbieEngine_Source/NewbieCamera.h"
#include "../NewbieEngine_Source/NewbieRenderer.h"
#include "../NewbieEngine_Source/NewbieAnimator.h"
#include "NewbieCat.h"
#include "NewbieCatScript.h"
#include "../NewbieEngine_Source/NewbieBoxCollider2D.h"
#include "../NewbieEngine_Source/NewbieCircleCollider2D.h"
#include "../NewbieEngine_Source/NewbieColliderManager.h"
#include "NewbieTile.h"
#include "NewbieTilemapRenderer.h"
#include "NewbieRigidbody.h"
#include "NewbieFloor.h"
#include "NewbieFloorScript.h"

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
		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		object::DontDestroyOnLoad(mPlayer);

		PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		collider->SetOffset(Vector2(-50.0f, -50.0f));

		// Set Player Texture
		graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
		//// Add Player Animation
		Animator* playerAnimator = mPlayer->AddComponent<Animator>();

		playerAnimator->CreateAnimation(L"Idle", playerTex,
			Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
		playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex,
			Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);

		playerAnimator->PlayAnimation(L"Idle", false);

		// 유저가 물줄시 고양이 생성 이벤트
		//playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, playerScript);

		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 250.0f));
		 // mPlayer->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

		Rigidbody* playerRigidbody =  mPlayer->AddComponent<Rigidbody>();
		playerRigidbody->SetMass(1.5f);
		playerRigidbody->SetFriction(30.0f);

		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(100.0f, 600.0f));
		floor->SetName(L"Floor");
		BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
		floorCol->SetSize(Vector2(3.0f, 1.0f));
		floor->AddComponent<FloorScript>();
		
		//// Make BackGround
		//GameObject* bg = object::Instantiate<GameObject>(enums::eLayerType::Player);
		//SpriteRenderer* bgSr = bg->AddComponent<SpriteRenderer>();
		//bgSr->SetSize(Vector2(1.1f, 1.1f));

		//// BackGround Texture
		//graphics::Texture* bgTexture = Resources::Find<graphics::Texture>(L"Bubble");
		//bgSr->SetTexture(bgTexture);

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
		ColliderManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		ColliderManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);

	}

	void PlayScene::OnExit()
	{
		/*Transform* tr = bg->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, 0));*/
	}
}