#pragma once

#include "Entity.h"
#include "NewbieComponent.h"


namespace newbie
{
	using namespace math;
	class Transform : public Component
	{
		// 위치, 좌표를 저장하는 요소로 각 객체에 부착
	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPosition(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		Vector2 GetPosition() { return mPosition; }
		float GetRotation() { return mRotation; }
		Vector2 GetScale() { return mScale; }
		void SetRotation(float rotate) { mRotation = rotate; }
		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;
	};
}