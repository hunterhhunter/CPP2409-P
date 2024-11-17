#pragma once
#include "NewbieGameObject.h"
#include "NewbieInput.h"
#include "NewbieTime.h"

namespace newbie
{
	GameObject::GameObject()
		: mX(0)
		, mY(0)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Update()
	{
		const int speed = 100.0f;

		// if (GetAsyncKeyState(VK_LEFT) & 0x8000)에서 Input 클래스로 변경
		if (Input::GetKey(eKeyCode::A))
		{
			// 11.14 프레임에 관계없이 일정한 거리 이동을 위한 Time::DeltaTime()으로 업데이트
			mX -= speed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mX += speed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			mY -= speed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mY += speed * Time::DeltaTime();
		}
	}
	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
		// 게임 오브젝트 렌더링      
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));

		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		SelectObject(hdc, oldPen);

		Rectangle(hdc, mX, mY, mX, mY);

		SelectObject(hdc, oldBrush);
		DeleteObject(blueBrush);
		DeleteObject(redPen);
	}
}