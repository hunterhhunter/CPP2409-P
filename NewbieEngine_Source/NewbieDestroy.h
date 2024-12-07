#pragma once
#include "NewbieGameObject.h"
namespace newbie::object
{	
	static void Destroy(class GameObject* obj)
	{
		if (obj != nullptr)
			obj->death();
	}
}