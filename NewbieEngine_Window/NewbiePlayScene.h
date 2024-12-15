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

		void CreateEnemy();

	private:
		class BackGround* bg;
		class Player* mPlayer;

		float mTime;
		float liveTime;
	};
}

