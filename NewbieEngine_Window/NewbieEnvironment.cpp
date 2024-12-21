#include "NewbieEnvironment.h"
#include "NewbieTransform.h"
#include "NewbieScene.h"
#include "NewbieSceneManager.h"
#include "NewbieResources.h"
#include "NewbieAnimator.h"
#include "NewbieCat.h"
#include "NewbieObject.h"
#include "NewbieScript.h"
#include "NewbieBoxCollider2D.h"
#include "NewbieEnemyScript.h"
#include <random>
#include <cmath>
#include "NewbieTime.h"

std::random_device rd;
std::mt19937 gen(rd()); // 난수 생성기
std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * PI); // 각도 θ (0 ~ 2π)
std::uniform_real_distribution<float> radiusDist(100.0f, 200.0f);    // 반지름 r (100 ~ 200)

namespace newbie
{
    Environment::Environment()
    {
        mTime = 0.0f;
    }

    void Environment::Reset() {
        learnState.playerPosition = { 0.0f, 0.0f };
        learnState.enemyPositions.clear();
    }

    double Environment::Step(int action) {
        // 플레이어 이동 처리
        if (action == 0) learnState.playerPosition.y -= 100.0f * Time::DeltaTime(); // 위
        else if (action == 1) learnState.playerPosition.y += 100.0f * Time::DeltaTime(); // 아래
        else if (action == 2) learnState.playerPosition.x -= 100.0f * Time::DeltaTime(); // 왼쪽
        else if (action == 3) learnState.playerPosition.x += 100.0f * Time::DeltaTime(); // 오른쪽
        // 정지(action == 4)는 아무것도 하지 않음

        double reward = 1.0; // 기본 생존 보상

        // 적과의 거리 계산 및 보상
        for (auto& enemy : learnState.enemyPositions) {
            double distance = sqrt(pow(learnState.playerPosition.x - enemy.x, 2) + pow(learnState.playerPosition.y - enemy.y, 2));
            reward -= distance * 0.1; // 거리 보상 (멀수록 보상 감소)
            if (distance < 1.0) return -100.0; // 충돌 시 큰 음의 보상
        }

        return reward;
    }

    void Environment::Initialize()
    {
        // 환경의 Init 플레이어 위치
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
        GameObject* Player = playerLayer->GetGameObjects().front();
        Transform* playerTr = Player->GetComponent<Transform>();
        learnState.playerPosition = playerTr->GetPosition();

        // 적 유닛 위치
        Layer* enemyLayer = activeScene->GetLayer(enums::eLayerType::Animal);
        std::vector<GameObject*> enemies = enemyLayer->GetGameObjects();
        for (auto& enemy : enemies)
        {
            Transform* enemyTr = enemy->GetComponent<Transform>();
            learnState.enemyPositions.push_back(enemyTr->GetPosition());
        }
    }

    void Environment::Update()
    {
        // 환경 업데이트
        // 플레이어 위치 업데이트
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
        GameObject* Player = playerLayer->GetGameObjects().front();
        Transform* playerTr = Player->GetComponent<Transform>();
        learnState.playerPosition = playerTr->GetPosition();

        // 적 유닛 위치 업데이트
        Layer* enemyLayer = activeScene->GetLayer(enums::eLayerType::Animal);
        std::vector<GameObject*> enemies = enemyLayer->GetGameObjects();
        for (auto& enemy : enemies)
        {
            Transform* enemyTr = enemy->GetComponent<Transform>();
            learnState.enemyPositions.push_back(enemyTr->GetPosition());
        }

        mTime += Time::DeltaTime();

        if (mTime > 1.0f)
        {
            spawnEnemy();
            mTime = 0;
        }
    }

    void Environment::LateUpdate()
    {
    }

    void Environment::Render(HDC hdc)
    {
    }

    // 적 생성 함수
    void Environment::spawnEnemy() {
        Vector2 playerPos = learnState.playerPosition;

        // 극좌표 생성
        float angle = angleDist(gen);  // θ
        float radius = radiusDist(gen); // r

        // 극좌표 -> 직교 좌표로 변환
        Vector2 newPos = Vector2(
            playerPos.x + radius * cos(angle),  // x = r * cos(θ)
            playerPos.y + radius * sin(angle)   // y = r * sin(θ)
        );

        graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Mario");
        Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
        cat->GetComponent<Transform>()->SetPosition(newPos);
        Script* catScript = cat->AddComponent<EnemyScript>();
        BoxCollider2D* mbc = cat->AddComponent<BoxCollider2D>();
        mbc->SetSize(Vector2(0.35f, 0.35f));
        Animator* mAnimator = cat->AddComponent<Animator>();
        mAnimator->CreateAnimation(L"Approching", playerTex,
            Vector2(373.0f, 1322.0f), Vector2(34.0f, 31.0f), Vector2::Zero, 2, 0.25f);
        mAnimator->PlayAnimation(L"Approching", true);
    }
}