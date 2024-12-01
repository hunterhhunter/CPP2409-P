#pragma once
#include "Commoninclude.h"
#include "NewbieBoxCollider2D.h"
#include "NewbieCircleCollider2D.h"

namespace newbie
{
	using namespace enums;

	class ColliderManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider* left, Collider* right);

	private:
		static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];
	};
}


