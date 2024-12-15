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
#include "NewbieEnemyScript.h"
#include "NewbieTime.h"
#include <random>
#include <cmath>

std::random_device rd;
std::mt19937 gen(rd()); // 난수 생성기
std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * PI); // 각도 θ (0 ~ 2π)
std::uniform_real_distribution<float> radiusDist(100.0f, 200.0f);    // 반지름 r (100 ~ 200)

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
		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(500.0f, 500.0f));
		mPlayer->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));

		cameraComp->SetTarget(mPlayer);

		PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		//collider->SetOffset(Vector2(5.0f, 5.0));
		collider->SetSize(Vector2(0.5f, 0.5f));
		collider->SetOffset(Vector2(0.0f, 5.0f));

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

		// 적 생성
		CreateEnemy();

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		mTime += Time::DeltaTime();
		
		if (mTime > 1.0f)
		{
			CreateEnemy();
			mTime = 0;
		}
		
		liveTime += Time::DeltaTime(); // 생존 시간
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
		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"Time : %0.2f", liveTime);
		int len = wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);

		Scene::Render(hdc);
	}

	void PlayScene::OnEnter()
	{
		ColliderManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
	}

	void PlayScene::OnExit()
	{
		/*Transform* tr = bg->GetComponent<Transform>();
		tr->SetPosition(Vector2(0, 0));*/
	}
	void PlayScene::CreateEnemy()
	{
		Transform* tr = mPlayer->GetComponent<Transform>();
		Vector2 playerPos = tr->GetPosition();

		// 극좌표 생성
		float angle = angleDist(gen);  // θ
		float radius = radiusDist(gen); // r

		// 극좌표 -> 직교 좌표로 변환
		Vector2 newPos = Vector2(
			playerPos.x + radius * cos(angle),  // x = r * cos(θ)
			playerPos.y + radius * sin(angle)   // y = r * sin(θ)
		);

		graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Mario");
		Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		cat->GetComponent<Transform>()->SetPosition(newPos);
		Script* catScript = cat->AddComponent<EnemyScript>();
		BoxCollider2D* mbc = cat->AddComponent<BoxCollider2D>();
		mbc->SetSize(Vector2(0.35f, 0.35f));
		Animator* mAnimator = cat->AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Approching", playerTex,
			Vector2(373.0f, 1322.0f), Vector2(34.0f, 31.0f), Vector2::Zero, 2, 0.25f);
		mAnimator->PlayAnimation(L"Approching");
	}
}