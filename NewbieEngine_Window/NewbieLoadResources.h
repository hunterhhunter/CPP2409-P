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

		Resources::Load<graphics::Texture>(
			L"Cat",
			L"C:/Users/slugg/Documents/GitHub/CPP2409-P/Resources/ChickenAlpha.bmp"
		);

		Resources::Load<graphics::Texture>(
			L"Bubble",
			L"../Resources/Bubble.png"
		);

		Resources::Load<graphics::Texture>(
			L"MapleEffect",
			L"../Resources/ezgif.com-gif-maker.png.png"
		);

		Resources::Load<graphics::Texture>(
			L"Player",
			L"C:/Users/slugg/Documents/GitHub/CPP2409-P/Resources/Player.bmp"
		);
	}
		
}