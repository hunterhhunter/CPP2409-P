#include "NewbiePlayScene.h"
#include "NewbieGameObject.h"
#include "NewbiePlayer.h"
#include "NewbieTransform.h"
#include "NewbieSpriteRenderer.h"

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
		//for (size_t i = 0; i < 100; i++)
		//{
		//	GameObject* obj = new GameObject();
		//	obj->SetPosition(rand() % 1600, rand() % 900);
		//	AddGameObject(obj);
		//}
		
		// 11.17 Component Struct 구축 후
		//{
		//	// Player 생성(GameObject의 mComponents 보유)
		//	Player* p1 = new Player();
		//	// 좌표, 위치를 나타내는 Transform 객체를 p1의 Components에 추가
		//	Transform* tr = p1->AddComponent<Transform>();
		//	tr->SetPos(800, 450);
		//	tr->SetName(L"TR1");
		//	// 렌더링하는 SpriteRenderer를 p1의 Components에 추가
		//	SpriteRenderer* sr = p1->AddComponent <SpriteRenderer>();
		//	sr->SetName(L"SR1");
		//	// Scene->PlayScene에 GameObject로 삽입
		//	AddGameObject(p1);
		//}

		// BackGround 유닛 추가
		{
			Player* bg = new Player();
			Transform* tr = bg->AddComponent<Transform>();
			tr->SetPos(Vector2(0, 0));
			tr->SetName(L"TR");

			SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");
			sr->ImageLoad(L"C:/Users/slugg/Documents/GitHub/CPP2409-P/Resources/BackGroundImage.jpg");
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}