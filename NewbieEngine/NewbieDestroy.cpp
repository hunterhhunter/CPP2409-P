#include "NewbieDestroy.h"
#include "NewbieGameObject.h"

namespace newbie
{
	namespace object
	{
		void Destroy(GameObject* obj)
		{
			obj->death();
		}
	}
}