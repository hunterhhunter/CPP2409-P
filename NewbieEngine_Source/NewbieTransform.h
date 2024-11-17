#pragma once

#include "Entity.h"
#include "NewbieComponent.h"

namespace newbie
{
	struct Pos
	{
		int mX;
		int mY;
	};

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

		void SetPos(int x, int y) { mX = x; mY = y; }
		int GetX() { return mX; }
		int GetY() { return mY; }

	private:
		int mX;
		int mY;
	};
}

