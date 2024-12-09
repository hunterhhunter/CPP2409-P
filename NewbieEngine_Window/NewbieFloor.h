#pragma once
#include "NewbieGameObject.h"

namespace newbie
{
	class Floor : public GameObject
	{
	public:
		Floor();
		~Floor();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};

}

