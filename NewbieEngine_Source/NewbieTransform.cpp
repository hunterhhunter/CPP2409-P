#include "NewbieTransform.h"
#include "NewbieRenderer.h"


newbie::Transform::Transform()
	: Component(enums::eComponentType::Transform)
	, mScale(Vector2::One)
	, mRotation(0.0f)
{
}

newbie::Transform::~Transform()
{
}

void newbie::Transform::Initialize()
{
}

void newbie::Transform::Update()
{
}

void newbie::Transform::LateUpdate()
{
}

void newbie::Transform::Render(HDC hdc)
{
	Vector2 pos = GetPosition();

	if (renderer::mainCamera)
		pos = renderer::mainCamera->CaluatePosition(pos);

	HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

	HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

	Rectangle(hdc, pos.x-1
		, pos.y-1
		, pos.x+1
		, pos.y+1);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(greenPen);
}
