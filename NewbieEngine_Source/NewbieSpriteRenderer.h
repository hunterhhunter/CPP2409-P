#pragma once
#include "NewbieComponent.h"
#include "Entity.h"

namespace newbie
{
	class SpriteRenderer : public Component
	{
		// 요소를 상속받아 Sprite를 렌더링하는 요소
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};
}

