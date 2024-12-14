#include "NewbiePlayerScript.h"
#include "NewbieInput.h"
#include "NewbieTransform.h"
#include "NewbieTime.h"
#include "NewbieGameObject.h"
#include "NewbieAnimator.h"
#include "NewbieCat.h"
#include "NewbieCatScript.h"
#include "NewbieObject.h"
#include "NewbieResources.h"
#include "NewbieRigidbody.h"
#include "NewbieBoxCollider2D.h"

namespace newbie
{
	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::Idle)
		, mAnimator(nullptr)
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case newbie::PlayerScript::eState::Idle:
			idle();
			break;
		case newbie::PlayerScript::eState::Walk:
			move();
			break;
		case newbie::PlayerScript::eState::Sleep:
			break;
		case newbie::PlayerScript::eState::GiveWater:
			giveWater();
			break;
		case newbie::PlayerScript::eState::Attack:
			break;
		default:
			break;
		}
	}
	
	void PlayerScript::LateUpdate()
	{

	}

	void PlayerScript::Render(HDC hdc)
	{

	}

	void PlayerScript::AttackEffect()
	{
	}

	void PlayerScript::idle()
	{
		if (Input::GetKey(eKeyCode::LButton))
		{
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (rb->GetGround() == true)
		{
			if (Input::GetKey(eKeyCode::D))
			{
					//pos.x += 100.0f * Time::DeltaTime();
					rb->AddForce(Vector2(300.0f, 0.0f));
					// 애니메이션
					mAnimator->PlayAnimation(L"RightRun", true);
					mState = newbie::PlayerScript::eState::Walk;

			}
			if (Input::GetKey(eKeyCode::A))
			{
					//pos.x -= 100.0f * Time::DeltaTime();
					rb->AddForce(Vector2(-300.0f, 0.0f));
					// 애니메이션
					mAnimator->PlayAnimation(L"LeftRun", true);
					mState = newbie::PlayerScript::eState::Walk;
			}
			if (Input::GetKey(eKeyCode::W))
			{
					Vector2 velocity = rb->GetVelocity();
					velocity.y = -700.0f;
					rb->SetVelocity(velocity);
					rb->SetGround(false);
			}
		}
		

		//tr->SetPosition(pos);

	}

	void PlayerScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (rb->GetGround() == true)
		{
			if (Input::GetKey(eKeyCode::D))
			{
				//pos.x += 100.0f * Time::DeltaTime();
				rb->AddForce(Vector2(200.0f, 0.0f));
			}
			if (Input::GetKey(eKeyCode::A))
			{
				//pos.x -= 100.0f * Time::DeltaTime();
				rb->AddForce(Vector2(-200.0f, 0.0f));
			}
			if (Input::GetKey(eKeyCode::W))
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -700.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
			}
		}

		//tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = PlayerScript::eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}

	void PlayerScript::giveWater()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		//other->GetOwner()->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 500.0f));
	}
	void PlayerScript::OnCollisionStay(Collider* other)
	{
	}
	void PlayerScript::OnCollisionExit(Collider* other)
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}
}