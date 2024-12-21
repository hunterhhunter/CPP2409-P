#pragma once
#include "Commoninclude.h"
#include "NewbieGameObject.h"
#include "NewbieMath.h"

namespace newbie
{

	struct State
	{
		Vector2 playerPosition; // �÷��̾� ��ġ [x, y]
		std::vector<Vector2> enemyPositions; // �� ��ġ [[x1, y1], [x2, y2], ...]
	};

	class Environment : public GameObject
	{
	public:
		Environment();

		void Reset(); // ȯ�� �ʱ�ȭ
		double Step(int action); // �ൿ ���� �� ���� ��ȯ

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		
		State GetLearnState() { return learnState; }

	private:
		float mTime;
		// �� ���� �Լ�
		void spawnEnemy();
		State learnState;
	};
}

