#include "NewbieFloor.h"
#include "NewbieCat.h"
#include "NewbieInput.h"
#include "NewbieTransform.h"
#include "NewbieTime.h"

namespace newbie
{
	Floor::Floor()
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
		GameObject::Initialize();
	}
	void Floor::Update()
	{
		GameObject::Update();
	}
	void Floor::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}