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
std::mt19937 gen(rd()); // ���� ������
std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * PI); // ���� �� (0 ~ 2��)
std::uniform_real_distribution<float> radiusDist(100.0f, 200.0f);    // ������ r (100 ~ 200)

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
        // �÷��̾� �̵� ó��
        if (action == 0) learnState.playerPosition.y -= 100.0f * Time::DeltaTime(); // ��
        else if (action == 1) learnState.playerPosition.y += 100.0f * Time::DeltaTime(); // �Ʒ�
        else if (action == 2) learnState.playerPosition.x -= 100.0f * Time::DeltaTime(); // ����
        else if (action == 3) learnState.playerPosition.x += 100.0f * Time::DeltaTime(); // ������
        // ����(action == 4)�� �ƹ��͵� ���� ����

        double reward = 1.0; // �⺻ ���� ����

        // ������ �Ÿ� ��� �� ����
        for (auto& enemy : learnState.enemyPositions) {
            double distance = sqrt(pow(learnState.playerPosition.x - enemy.x, 2) + pow(learnState.playerPosition.y - enemy.y, 2));
            reward -= distance * 0.1; // �Ÿ� ���� (�ּ��� ���� ����)
            if (distance < 1.0) return -100.0; // �浹 �� ū ���� ����
        }

        return reward;
    }

    void Environment::Initialize()
    {
        // ȯ���� Init �÷��̾� ��ġ
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
        GameObject* Player = playerLayer->GetGameObjects().front();
        Transform* playerTr = Player->GetComponent<Transform>();
        learnState.playerPosition = playerTr->GetPosition();

        // �� ���� ��ġ
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
        // ȯ�� ������Ʈ
        // �÷��̾� ��ġ ������Ʈ
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
        GameObject* Player = playerLayer->GetGameObjects().front();
        Transform* playerTr = Player->GetComponent<Transform>();
        learnState.playerPosition = playerTr->GetPosition();

        // �� ���� ��ġ ������Ʈ
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

    // �� ���� �Լ�
    void Environment::spawnEnemy() {
        Vector2 playerPos = learnState.playerPosition;

        // ����ǥ ����
        float angle = angleDist(gen);  // ��
        float radius = radiusDist(gen); // r

        // ����ǥ -> ���� ��ǥ�� ��ȯ
        Vector2 newPos = Vector2(
            playerPos.x + radius * cos(angle),  // x = r * cos(��)
            playerPos.y + radius * sin(angle)   // y = r * sin(��)
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