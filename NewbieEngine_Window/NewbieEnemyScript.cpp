#include "NewbieEnemyScript.h"
#include "NewbieTransform.h"
#include "NewbieBoxCollider2D.h"
#include "NewbieTime.h"
#include "NewbieGameObject.h"
#include "NewbieAnimator.h"
#include "NewbieObject.h"

namespace newbie
{
	EnemyScript::EnemyScript()
	{

	}

	EnemyScript::~EnemyScript(
	)
	{
	}
	void EnemyScript::Initialize()
	{
	}
	void EnemyScript::Update()
	{
		Transform* mtr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = mtr->GetPosition();

		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);

		if (!playerLayer->GetGameObjects().empty())
		{
			GameObject* player = playerLayer->GetGameObjects().front();
			Transform* tr = player->GetComponent<Transform>();
			Vector2 playerPs = tr->GetPosition();

			Vector2 direction = playerPs - pos;
			direction.normalize();

			float speed = 80.0f;
			pos += (direction * speed * Time::DeltaTime());
			mtr->SetPosition(pos);
		}
	}

	void EnemyScript::LateUpdate()
	{
	}
	void EnemyScript::Render(HDC hdc)
	{
	}
	void EnemyScript::OnCollisionEnter(Collider* other)
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
		Layer* envLayer = activeScene->GetLayer(enums::eLayerType::BackGround);

		if (!playerLayer->GetGameObjects().empty())
		{
			GameObject* player = playerLayer->GetGameObjects().front();
			BoxCollider2D* bc = player->GetComponent<BoxCollider2D>();

			if (other == bc)
			{
				Environment* env = envLayer->GetEnvironment();
				if (env) {
					env->ApplyPenalty(-100.0); // 충돌 페널티 기록
				}

				env->RestartGame();
			}
		}
	}
	void EnemyScript::OnCollisionStay(Collider* other)
	{
	}
	void EnemyScript::OnCollisionExit(Collider* other)
	{
	}
}