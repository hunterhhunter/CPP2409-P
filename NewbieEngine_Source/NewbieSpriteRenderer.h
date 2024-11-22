#pragma once
#include "NewbieComponent.h"
#include "Entity.h"
#include "NewbieTexture.h"

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
		void SetTexture(graphics::Texture* texture) { mTexture = texture; }
		void SetSize(math::Vector2 size) { mSize = size; }

	private:
		graphics::Texture* mTexture;
		math::Vector2 mSize;
	};
}

