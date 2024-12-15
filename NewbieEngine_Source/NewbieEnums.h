#pragma once
namespace newbie
{
	namespace enums
	{
		enum class eLayerType
		{
			None,
			BackGround,
			Tile,
			Animal,
			Floor,
			Player,
			Particle,
			Max = 16,
		};

		enum class eResourceType
		{
			Texture,
			AudioClip,
			Animation,
			Prefab,
			End,
		};

		enum class eComponentType
		{
			Transform,
			Collider,
			Rigidbody,
			Script,
			SpriteRenderer,
			Animator,
			Camera,
			End,
		};

		enum class eColliderType
		{
			Circle2D,
			Rect2D,
			End,
		};
	}
}