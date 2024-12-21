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
        // Init에 Env 가져오기
        Scene* scene = SceneManager::GetActiveScene();
        Layer* layer = scene->GetLayer(enums::eLayerType::BackGround);
        Environment* env = layer->GetEnvironment();
        learnState = env->GetLearnState();  // learnState를 환경 상태로 초기화
    }
    void QLearningAgent::Update()
    {
        // 매 업데이트마다 초기화
        Scene* scene = SceneManager::GetActiveScene();
        Layer* layer = scene->GetLayer(enums::eLayerType::BackGround);
        Environment* env = layer->GetEnvironment();

        Layer* playerLayer = scene->GetLayer(enums::eLayerType::Player);
        GameObject* player = playerLayer->GetGameObjects().front();

        // 환경 상태 가져오기
        const State& currentState = env->GetLearnState();

        int action = chooseAction(learnState, epsilon);

        // epsilon을 지수적으로 감소
        epsilon *= 0.995;  // 0.995씩 곱해서 점차 감소
        if (epsilon < 0.1) {
            epsilon = 0.1;  // 최소 epsilon 값 설정
        }
        double reward = 0.0;

        if (env != nullptr)
        {
            // reward 계산
            reward = env->Step(action);

            Transform* tr = player->GetComponent<Transform>();

            // 다음 상태 가져오기
            const State& nextState = env->GetLearnState();

            tr->SetPosition(nextState.playerPosition);

            // Q-값 업데이트
            updateQValue(currentState, action, reward, nextState, alpha, gamma);
        }
    }

    void QLearningAgent::LateUpdate()
    {
    }

    void QLearningAgent::Render(HDC hdc)
    {
    }

    // 생성자: Q-테이블 초기화
    QLearningAgent::QLearningAgent()
    {
        epsilon = 1.0;
    }

    // 행동 결정
    int QLearningAgent::chooseAction(const State& state, double epsilon)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        if (dis(gen) < epsilon) {
            // 탐험: 랜덤 행동
            return rand() % numActions;
        }
        else {
            // 활용: 최적 행동 선택
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
