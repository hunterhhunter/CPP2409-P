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
        lastPenalty = 0.0;
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
        else if (action == 4) { // 좌상
            learnState.playerPosition.x -= 70.7f * Time::DeltaTime();
            learnState.playerPosition.y -= 700.7f * Time::DeltaTime();
        }
        else if (action == 5) { // 우상
            learnState.playerPosition.x += 700.7f * Time::DeltaTime();
            learnState.playerPosition.y -= 700.7f * Time::DeltaTime();
        }
        else if (action == 6) { // 좌하
            learnState.playerPosition.x -= 70.7f * Time::DeltaTime();
            learnState.playerPosition.y += 70.7f * Time::DeltaTime();
        }
        else if (action == 7) { // 우하
            learnState.playerPosition.x += 70.7f * Time::DeltaTime();
            learnState.playerPosition.y += 70.7f * Time::DeltaTime();
        }


        double reward = 1.0; // 기본 생존 보상
        const double distanceScale = 0.1; // 거리 보상 스케일링 계수

        // 적과의 거리 계산 및 보상
        for (auto& enemy : learnState.enemyPositions) {
            double distance = sqrt(pow(learnState.playerPosition.x - enemy.x, 2) + pow(learnState.playerPosition.y - enemy.y, 2));
            reward += distance * distanceScale; // 거리가 멀수록 보상 증가
        }

        // 페널티를 보상에 포함
        reward += lastPenalty;

        // 페널티 초기화 (1회 적용)
        lastPenalty = 0.0;

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

        if (mTime > 0.3f)
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

    void Environment::ApplyPenalty(double penalty)
    {
        lastPenalty = penalty; // 페널티 기록
    }

    double Environment::GetLastPenalty() const
    {
        return lastPenalty; // 마지막 페널티 반환
    }

    void Environment::RestartGame()
    {
        Scene* activeScene = SceneManager::GetActiveScene();

        // 플레이어 위치 초기화
        Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
        if (!playerLayer->GetGameObjects().empty()) {
            GameObject* player = playerLayer->GetGameObjects().front();
            Transform* playerTransform = player->GetComponent<Transform>();
            playerTransform->SetPosition(Vector2(500.0f, 500.0f)); // 초기 위치
        }

        DeleteEnemy();

        // 학습 환경 초기화
        Layer* layer = activeScene->GetLayer(enums::eLayerType::BackGround);
        Environment* env = layer->GetEnvironment();
        if (env) {
            env->Reset(); // 환경 상태 초기화
        }
    }

    void Environment::DeleteEnemy(GameObject* enemy)
    {
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* enemyLayer = activeScene->GetLayer(enums::eLayerType::Animal);

        if (enemy == nullptr) {
            // 모든 적 삭제
            std::vector<GameObject*> enemies = enemyLayer->GetGameObjects();
            for (GameObject* enemyObj : enemies) {
                object::Destroy(enemyObj); // 개별 적 삭제
            }
        }
        else {
            // 특정 적 삭제
            object::Destroy(enemy);
        }

        // 상태 정보 업데이트 (필요 시)
        learnState.enemyPositions.clear(); // 적 위치 초기화
        std::vector<GameObject*> remainingEnemies = enemyLayer->GetGameObjects();
        for (GameObject* enemyObj : remainingEnemies) {
            Transform* enemyTransform = enemyObj->GetComponent<Transform>();
            learnState.enemyPositions.push_back(enemyTransform->GetPosition());
        }
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