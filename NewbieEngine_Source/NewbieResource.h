#pragma once

#include "Entity.h"

namespace newbie
{
	class Resource abstract : public Entity
		// 추상 클래스 메모리 할당 X
		// 상속용
	{
	public:
		Resource(enums::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;
		// 가상함수, 실제 메모리 할당이 안됨

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		const enums::eResourceType mType;
		std::wstring mPath;
	};
}