#include "NewbieRigidbody.h"
#include "NewbieTime.h"
#include "NewbieTransform.h"
#include "NewbieGameObject.h"
#include "NewbieTransform.h"
#include "NewbieGameObject.h"
#include "NewbieCamera.h"
#include "NewbieRenderer.h"
#include "NewbieBoxCollider2D.h"

namespace newbie
{
	Rigidbody::Rigidbody()
		: Component(enums::eComponentType::Rigidbody)
		, mbGround(false)
		, mMass(1.0f)
		, mFriction(10.0f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mLimitedVelocity(Vector2(200.0f, 1000.0f))
		, mGravity(Vector2(0.0f, 800.0f))
		, mAccelation(Vector2::Zero)
	{
	}

	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		// f = m * a
		// a = f / m
		mAccelation = mForce / mMass;

		// v = v.prev + acc
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// 땅 위에 있을 때
			Vector2 gravity = mGravity;
			gravity.normalize();

			float dot = Vector2::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을 떄
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		Vector2 gravity = mGravity;
		// 단위벡터(방향)
		gravity.normalize();
		// 중력 방향의 가속도 구하기
		float dot = Vector2::Dot(mVelocity, gravity);
		// 중력 방향으로 속도 계산
		gravity = gravity * dot;

		// 중력 방향이 아닌 방향으로의 속도
		Vector2 sideVelocity = mVelocity - gravity;

		// 속도 제한
		if (mLimitedVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < gravity.length())
		{
			gravity.normalize();
			gravity *= mLimitedVelocity.x;
		}

		mVelocity = gravity + sideVelocity;

		if (!(mVelocity == Vector2::Zero))
		{
			// 마찰력 작용 구현
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량 > 현재 속도
			if (mVelocity.length() <= friction.length())
			{
				// 멈추기
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}

			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos = pos + mVelocity * Time::DeltaTime();
			tr->SetPosition(pos);

			mForce.clear();
		}
	}

	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
}