#pragma once
#include "NewbieScene.h"

namespace newbie
{
	class DontDestroyOnLoad : public Scene
	{
		// DontDestroyOnLoad는 씬 변경시에도 게임 오브젝트가 사라지지 않도록 하는 역할
		// 전의 씬에서 DontDestroy씬으로 옮기는 방식으로 사라지지 않도록 함
		//
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;
	};

}
