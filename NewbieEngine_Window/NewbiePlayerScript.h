#pragma once
#include "../NewbieEngine_Source/NewbieScript.h"

namespace newbie
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Walk,
			Idle,
			Sleep,
			GiveWater,
			Attack,
		};

		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		void idle();
		void move();
		void giveWater();

	private:
		eState mState;
		class Animator* mAnimator;
	};
}

