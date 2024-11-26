#pragma once

#include "../NewbieEngine_Source/NewbieResources.h"
#include "../NewbieEngine_Source/NewbieTexture.h"

namespace newbie
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(
			L"BG",
			L"../Resources/BackGroundImage.png"
		);
		
		Resources::Load<graphics::Texture>(
			L"PLAYER",
			L"../Resources/cha.png"
		);

		Resources::Load<graphics::Texture>(
			L"Map",
			L"../Resources/img/map/map_pure.png"
		);

		Resources::Load<graphics::Texture>(
			L"PackMan",
			L"../Resources/img/pacman/0.png"
		);
	}
		
}