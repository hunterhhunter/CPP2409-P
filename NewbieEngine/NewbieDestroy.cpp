#include "NewbieDestroy.h"
#include "NewbieGameObject.h"

namespace Newbie::object
{
	void Destroy(GameObject* obj)
	{
		obj->Death();
	}
}