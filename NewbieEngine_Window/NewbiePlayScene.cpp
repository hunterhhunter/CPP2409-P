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
		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 0.0f));
		mPlayer->GetComponent<Transform>()->SetScale(Vector2(1.5f, 1.5f));

		Rigidbody* playerRigidbody =  mPlayer->AddComponent<Rigidbody>();
		playerRigidbody->SetMass(1.5f);
		playerRigidbody->SetFriction(30.0f);

		cameraComp->SetTarget(mPlayer);

		PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		collider->SetOffset(Vector2(-15.0f, -15.0f));
		collider->SetSize(Vector2(1.0f, 1.0f));

		// Set Player Texture
		graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Mario");
		//// Add Player Animation
		Animator* playerAnimator = mPlayer->AddComponent<Animator>();

		playerAnimator->CreateAnimation(L"Idle", playerTex,
			Vector2(72.0f, 985.0f), Vector2(31.0f, 63.0f), Vector2::Zero, 1, 0.1f);
		playerAnimator->CreateAnimation(L"RightRun", playerTex,
			Vector2(204.0f, 987.0f), Vector2(42.0f, 62.0f), Vector2::Zero, 2, 0.25f);
		playerAnimator->CreateAnimation(L"LeftRun", playerTex,
			Vector2(206.0f, 1599.0f), Vector2(45.0f, 62.0f), Vector2::Zero, 2, 0.25f);

		playerAnimator->PlayAnimation(L"Idle", false);

		

		Vector2 gap = Vector2(32.0f, 0.0f);
		for (int row = 0; row < 1; ++row) {
			for (int col = 0; col < 30; ++col) {
				Floor* floor = object::Instantiate<Floor>(eLayerType::Floor);
				Transform* floorTr = floor->AddComponent<Transform>();

				// 위치 설정: 시작 위치 + 간격 * (행, 열)
				Vector2 position = Vector2(100.0f, 300.0f) + Vector2(col * gap.x, row * gap.y);
				floorTr->SetPosition(position);
				floor->SetName(L"Floor");

				// 박스 콜라이더 설정
				BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
				floorCol->SetSize(Vector2(1.0f, 1.0f));
				floorCol->SetOffset(Vector2(10.0f, 10.0f));

				// 애니메이션 설정
				/*Animator* floorAnimator = floor->AddComponent<Animator>();
				floor->AddComponent<FloorScript>();
				floorAnimator->CreateAnimation(L"BasicTile", playerTex,
					Vector2(244.0f, 137.0f), Vector2(33.0f, 33.0f), Vector2::Zero, 1, 0.1f);
				floorAnimator->PlayAnimation(L"BasicTile", false);*/
			}
		}
		
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