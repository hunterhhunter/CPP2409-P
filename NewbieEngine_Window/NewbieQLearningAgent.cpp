#include "NewbieQLearningAgent.h"
#include <random>
#include <limits>
#include "NewbieSceneManager.h"
#include "NewbieScene.h"
#include "NewbieTransform.h"

namespace newbie
{
    void QLearningAgent::Initialize()
    {
        // Init�� Env ��������
        Scene* scene = SceneManager::GetActiveScene();
        Layer* layer = scene->GetLayer(enums::eLayerType::BackGround);
        Environment* env = layer->GetEnvironment();
        learnState = env->GetLearnState();  // learnState�� ȯ�� ���·� �ʱ�ȭ
    }
    void QLearningAgent::Update()
    {
        // �� ������Ʈ���� �ʱ�ȭ
        Scene* scene = SceneManager::GetActiveScene();
        Layer* layer = scene->GetLayer(enums::eLayerType::BackGround);
        Environment* env = layer->GetEnvironment();

        Layer* playerLayer = scene->GetLayer(enums::eLayerType::Player);
        GameObject* player = playerLayer->GetGameObjects().front();

        // ȯ�� ���� ��������
        const State& currentState = env->GetLearnState();

        action = chooseAction(learnState, epsilon);

        // epsilon�� ���������� ����
        epsilon *= 0.999;  // 0.995�� ���ؼ� ���� ����
        if (epsilon < 0.3) {
            epsilon = 0.3;  // �ּ� epsilon �� ����
        }
        double reward = 0.0;

        // reward ���
        reward = env->Step(action);
        reward += env->GetLastPenalty(); // ���Ƽ�� �߰��� �ݿ�

        Transform* tr = player->GetComponent<Transform>();

        // ���� ���� ��������
        const State& nextState = env->GetLearnState();

        tr->SetPosition(nextState.playerPosition);

        // Q-�� ������Ʈ
        updateQValue(currentState, action, reward, nextState, alpha, gamma);

        learnState = nextState; // ���� ���·� ����
    }

    void QLearningAgent::LateUpdate()
    {
    }

    void QLearningAgent::Render(HDC hdc)
    {
        wchar_t str[50] = L"";
        swprintf_s(str, 50, L"Action : %d", action);
        int len = wcsnlen_s(str, 50);

        TextOut(hdc, 100, 0, str, len);
    }

    // ������: Q-���̺� �ʱ�ȭ
    QLearningAgent::QLearningAgent()
    {
        epsilon = 1.0;
    }

    // �ൿ ����
    int QLearningAgent::chooseAction(const State& state, double epsilon)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        if (dis(gen) < epsilon) {
            // Ž��: ���� �ൿ
            return rand() % numActions;
        }
        else {
            // Ȱ��: ���� �ൿ ����
            int bestAction = 0;
            double maxQ = std::numeric_limits<double>::lowest();
            for (int action = 0; action < numActions; ++action) {
                double qValue = Q[{state.playerPosition, action}];
                if (qValue > maxQ) {
                    maxQ = qValue;
                    bestAction = action;
                }
            }
            return bestAction;
        }
    }

    void QLearningAgent::updateQValue(const State& currentState, int action, double reward, const State& nextState, double alpha, double gamma)
    {
        double maxNextQ = std::numeric_limits<double>::lowest();
        for (int nextAction = 0; nextAction < numActions; ++nextAction) {
            double qval = getQValue(nextState.playerPosition, nextAction);
            if (maxNextQ < qval)
            {
                maxNextQ = qval;
            }
        }

        double currentQ = getQValue(currentState.playerPosition, action);
        setQValue(currentState.playerPosition, action, currentQ + alpha * (reward + gamma * maxNextQ - currentQ));
    }
}