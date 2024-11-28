#include "NewbieTransform.h"

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
}
