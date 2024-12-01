#include "NewbieDestroy.h"
#include "NewbieGameObject.h"

namespace newbie::object
{
	void Destroy(GameObject* obj)
	{
		obj->Death();
	}
}