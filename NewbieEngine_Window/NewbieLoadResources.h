#pragma once

#include "../NewbieEngine_Source/NewbieResources.h"
#include "../NewbieEngine_Source/NewbieTexture.h"

namespace newbie
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(
			L"BG",
			L"C:/Users/slugg/Documents/GitHub/CPP2409-P/Resources/BackGroundImage.png"
		);
	}
		
}