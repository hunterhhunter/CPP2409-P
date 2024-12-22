#pragma once
#include "../NewbieEngine_Source/NewbieScript.h"
#include "Commoninclude.h"
#include "NewbieEnvironment.h"
#include "NewbieGameObject.h"

namespace newbie
{
	class QLearningAgent : public Script
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		QLearningAgent();

		// �ൿ ���� (Ž��/Ȱ��)
		int chooseAction(const State& state, double epsilon);

		// Q-�� ������Ʈ
		void updateQValue(const State& currentState, int action, double reward, const State& nextState, double alpha, double gamma);


	private:
		void setQValue(const Vector2& position, int action, double value) {
			auto key = std::make_pair(position, action);
			Q[key] = value;
		}

		double getQValue(const Vector2& position, int action) {
			auto key = std::make_pair(position, action);
			if (Q.find(key) == Q.end()) {
				Q[key] = 0.0; // Q-�� �ʱ�ȭ
			}
			return Q[key];
		}

	private:
		std::map<std::pair<Vector2, int>, double> Q; // Q-���̺�: ����-�ൿ ��
		int numActions = 9;
		State learnState;
		double epsilon;
		const double alpha = 0.1;
		const double gamma = 0.99;
	};
}

