#include "NewbieColliderManager.h"
#include "NewbieScene.h"
#include "NewbieSceneManager.h"
#include "NewbieGameObject.h"
#include "NewbieCollider.h"

namespace newbie
{
	std::bitset<(UINT)eLayerType::Max> ColliderManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	
	void ColliderManager::Initialize()
	{
		int a = 1;
		int b = a << 1;
	}

	void ColliderManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void ColliderManager::LateUpdate()
	{
	}
	void ColliderManager::Render(HDC hdc)
	{
	}

	void ColliderManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;
	}

	void ColliderManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();
		
		for (GameObject* left : lefts)
		{
			if (left->IsActive() == false)
				continue;

			Collider* leftCol = left->GetComponent<Collider>();

			if (leftCol == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				if (right->IsActive() == false)
					continue;

				Collider* rightCol = right->GetComponent<Collider>();
				
				if (rightCol == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void ColliderManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 충돌 체크 로직 구현
	}
}