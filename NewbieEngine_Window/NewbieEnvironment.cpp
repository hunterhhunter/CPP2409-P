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
        lastPenalty = 0.0;
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
        else if (action == 4) { // �»�
            learnState.playerPosition.x -= 70.7f * Time::DeltaTime();
            learnState.playerPosition.y -= 700.7f * Time::DeltaTime();
        }
        else if (action == 5) { // ���
            learnState.playerPosition.x += 700.7f * Time::DeltaTime();
            learnState.playerPosition.y -= 700.7f * Time::DeltaTime();
        }
        else if (action == 6) { // ����
            learnState.playerPosition.x -= 70.7f * Time::DeltaTime();
            learnState.playerPosition.y += 70.7f * Time::DeltaTime();
        }
        else if (action == 7) { // ����
            learnState.playerPosition.x += 70.7f * Time::DeltaTime();
            learnState.playerPosition.y += 70.7f * Time::DeltaTime();
        }


        double reward = 1.0; // �⺻ ���� ����
        const double distanceScale = 0.1; // �Ÿ� ���� �����ϸ� ���

        // ������ �Ÿ� ��� �� ����
        for (auto& enemy : learnState.enemyPositions) {
            double distance = sqrt(pow(learnState.playerPosition.x - enemy.x, 2) + pow(learnState.playerPosition.y - enemy.y, 2));
            reward += distance * distanceScale; // �Ÿ��� �ּ��� ���� ����
        }

        // ���Ƽ�� ���� ����
        reward += lastPenalty;

        // ���Ƽ �ʱ�ȭ (1ȸ ����)
        lastPenalty = 0.0;

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
        lastPenalty = penalty; // ���Ƽ ���
    }

    double Environment::GetLastPenalty() const
    {
        return lastPenalty; // ������ ���Ƽ ��ȯ
    }

    void Environment::RestartGame()
    {
        Scene* activeScene = SceneManager::GetActiveScene();

        // �÷��̾� ��ġ �ʱ�ȭ
        Layer* playerLayer = activeScene->GetLayer(enums::eLayerType::Player);
        if (!playerLayer->GetGameObjects().empty()) {
            GameObject* player = playerLayer->GetGameObjects().front();
            Transform* playerTransform = player->GetComponent<Transform>();
            playerTransform->SetPosition(Vector2(500.0f, 500.0f)); // �ʱ� ��ġ
        }

        DeleteEnemy();

        // �н� ȯ�� �ʱ�ȭ
        Layer* layer = activeScene->GetLayer(enums::eLayerType::BackGround);
        Environment* env = layer->GetEnvironment();
        if (env) {
            env->Reset(); // ȯ�� ���� �ʱ�ȭ
        }
    }

    void Environment::DeleteEnemy(GameObject* enemy)
    {
        Scene* activeScene = SceneManager::GetActiveScene();
        Layer* enemyLayer = activeScene->GetLayer(enums::eLayerType::Animal);

        if (enemy == nullptr) {
            // ��� �� ����
            std::vector<GameObject*> enemies = enemyLayer->GetGameObjects();
            for (GameObject* enemyObj : enemies) {
                object::Destroy(enemyObj); // ���� �� ����
            }
        }
        else {
            // Ư�� �� ����
            object::Destroy(enemy);
        }

        // ���� ���� ������Ʈ (�ʿ� ��)
        learnState.enemyPositions.clear(); // �� ��ġ �ʱ�ȭ
        std::vector<GameObject*> remainingEnemies = enemyLayer->GetGameObjects();
        for (GameObject* enemyObj : remainingEnemies) {
            Transform* enemyTransform = enemyObj->GetComponent<Transform>();
            learnState.enemyPositions.push_back(enemyTransform->GetPosition());
        }
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