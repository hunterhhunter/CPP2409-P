#pragma once
#include "Commoninclude.h"
using namespace newbie::math;


namespace newbie {
	// 디버깅 되는 모든 객체가 상속받을 객체
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }

	private:
		std::wstring mName;
	};
}

