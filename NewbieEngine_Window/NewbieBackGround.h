#pragma once
#include "../NewbieEngine_Source/NewbieGameObject.h"

namespace newbie
{
	class BackGround : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}