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

		// GetEnvironment 반환 함수 추가
		Environment* GetEnvironment()
		{
			for (GameObject* obj : GetGameObjects())
			{
				// GameObject가 Environment로 변환 가능한지 확인
				Environment* env = dynamic_cast<Environment*>(obj);
				if (env != nullptr)
					return env;
			}
			return nullptr;  // 해당 레이어에 Environment가 없다면 nullptr 반환
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

