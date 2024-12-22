#pragma once
#include "Entity.h"
#include "CommonInclude.h"
#include "NewbieGameObject.h"
#include "../NewbieEngine_Window/NewbieEnvironment.h"

namespace newbie
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		void AddGameObject(GameObject* gameObject);
		void EraseGameObject(GameObject* eraseGameObj);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }

		// GetEnvironment ��ȯ �Լ� �߰�
		Environment* GetEnvironment()
		{
			for (GameObject* obj : GetGameObjects())
			{
				// GameObject�� Environment�� ��ȯ �������� Ȯ��
				Environment* env = dynamic_cast<Environment*>(obj);
				if (env != nullptr)
					return env;
			}
			return nullptr;  // �ش� ���̾ Environment�� ���ٸ� nullptr ��ȯ
		}

	private:
		void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
		void deleteGameObjects(std::vector<GameObject*> gameObjs);
		void eraseDeadGameObject();

	private:
		std::vector<GameObject*> mGameObjects;
	};

	typedef std::vector<GameObject*>::iterator GameObjectIter;
}

