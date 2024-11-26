#pragma once

namespace newbie
{
	namespace enums
	{
		enum class eLayerType
		{
			None,
			BackGround,
			Player,
			Max = 16,
		};

		enum class eResourceType
		{
			Texture,
			AudioClip,
			Prefab,
			End,
		};

		enum class eComponentType
		{
			Transform,
			SpriteRenderer,
			Script,
			Camera,
			End,
		};
	}
}