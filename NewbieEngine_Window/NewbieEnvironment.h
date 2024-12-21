#pragma once
#include "Commoninclude.h"
#include "NewbieGameObject.h"
#include "NewbieMath.h"

namespace newbie
{

	struct State
	{
		Vector2 playerPosition; // 플레이어 위치 [x, y]
		std::vector<Vector2> enemyPositions; // 적 위치 [[x1, y1], [x2, y2], ...]
	};

	class Environment : public GameObject
	{
	public:
		Environment();

		void Reset(); // 환경 초기화
		double Step(int action); // 행동 수행 및 보상 반환

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		
		State GetLearnState() { return learnState; }

	private:
		float mTime;
		// 적 생성 함수
		void spawnEnemy();
		State learnState;
	};
}

