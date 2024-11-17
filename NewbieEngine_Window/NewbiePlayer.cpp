#include "NewbiePlayer.h"
#include "NewbieInput.h"
#include "NewbieTransform.h"
#include "NewbieTime.h"

namespace newbie
{
	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		if (Input::GetKey(eKeyCode::Right))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 Pos = tr->Ge
		}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}