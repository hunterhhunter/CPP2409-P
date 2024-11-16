#pragma once
#include "NewbieScene.h"

namespace newbie
{
	class SceneManager
	{
		// 씬을 관리하는 manager class
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			scene->Initialize();

			mScene.insert(std::make_pair(name, scene));
		}



		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private:
		static std::map<std::wstring, Scene*> mScene; // 씬 벡터
		static Scene* mactiveScene; // 실행시킬 씬
	};
}

