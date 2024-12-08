#pragma once
#include "../NewbieEngine_Source/NewbieGameObject.h"
namespace newbie
{
	class Tile : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPosition(int x, int y);

	private:
	};

}

