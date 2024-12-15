#pragma once
#include "../NewbieEngine_Source/NewbieScript.h"
#include "../NewbieEngine_Source/NewbieTransform.h"

namespace newbie
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	private:
	};
}
