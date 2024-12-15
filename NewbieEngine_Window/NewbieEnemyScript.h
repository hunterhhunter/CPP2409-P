#pragma once
#include "NewbieScript.h"
#include "NewbieTransform.h"

namespace newbie
{
	class EnemyScript : public Script
	{
	public:
		EnemyScript();
		~EnemyScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:

	};

}

