#include "NewbieCatScript.h"
#include "NewbieInput.h"
#include "NewbieTransform.h"
#include "NewbieTime.h"
#include "NewbieGameObject.h"
#include "NewbieAnimator.h"


namespace newbie
{
	CatScript::CatScript()
		: mState(CatScript::eState::SitDown)
		, mAnimator(nullptr)
		, mTime(0.0f)
	{
	}

	CatScript::~CatScript()
	{

	}

	void CatScript::Initialize()
	{

	}

	void CatScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case newbie::CatScript::eState::SitDown:
			sitDown();
			break;
		case newbie::CatScript::eState::Walk:
			move();
			break;
		case newbie::CatScript::eState::Sleep:
			break;
		case newbie::CatScript::eState::LayDown:
			layDown();
			break;
		case newbie::CatScript::eState::Attack:
			break;
		default:
			break;
		}
	}

	void CatScript::LateUpdate()
	{

	}

	void CatScript::Render(HDC hdc)
	{

	}

	void CatScript::sitDown()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			mState = CatScript::eState::Walk;
			int direction = (rand() % 4);
			mDirection = (eDirection)direction;
			PlayWalkAnimationByDirection(mDirection);
			mTime = 0.0f;
		}
	}

	void CatScript::move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			int isLayDown = rand() % 2;
			if (isLayDown)
			{
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LayDown", false);
			}
			else
			{
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SitDown", false);
			}
		}
		
		Transform* tr = GetOwner()->GetComponent<Transform>();
		translate(tr);
	}

	void CatScript::layDown()
	{
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			mState = CatScript::eState::Walk;
			int direction = (rand() % 4);
			mDirection = (eDirection)direction;
			PlayWalkAnimationByDirection(mDirection);
			mTime = 0.0f;
		}
	}

	void CatScript::PlayWalkAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case newbie::CatScript::eDirection::Left:
			mAnimator->PlayAnimation(L"LeftWalk", true);
			break;
		case newbie::CatScript::eDirection::Right:
			mAnimator->PlayAnimation(L"RightWalk", true);
			break;
		case newbie::CatScript::eDirection::Down:
			mAnimator->PlayAnimation(L"DownWalk", true);
			break;
		case newbie::CatScript::eDirection::Up:
			mAnimator->PlayAnimation(L"UpWalk", true);
			break;
		default:
			assert(false);
			break;
		}
	}

	void CatScript::translate(Transform* tr)
	{
		Vector2 pos = tr->GetPosition();
		switch (mDirection)
		{
		case newbie::CatScript::eDirection::Left:
			pos.x -= 100.0f * Time::DeltaTime();
			break;
		case newbie::CatScript::eDirection::Right:
			pos.x += 100.0f * Time::DeltaTime();
			break;
		case newbie::CatScript::eDirection::Down:
			pos.y += 100.0f * Time::DeltaTime();
			break;
		case newbie::CatScript::eDirection::Up:
			pos.y -= 100.0f * Time::DeltaTime();
			break;
		default:
			assert(false);
			break;
		}
		tr->SetPosition(pos);
	}
}