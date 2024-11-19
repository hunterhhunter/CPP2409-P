#pragma once
#include "NewbieScene.h"
#include "NewbieBackGround.h"

namespace newbie
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit()  override;

	private:
		class BackGround* bg;
		class Player* player;
	};
}

