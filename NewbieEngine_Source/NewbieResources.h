#pragma once
#include "NewbieResource.h"

namespace newbie
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			auto iter = mResources.fine(key);
			if (iter == mResource.end())
				return nullptr;
			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(path)))
				assert(false);

			resource->SetName(key);
			resource->SetPath(path);
			mResorces.insert(std::make_pair(key, resource));

			return resource;
		}
		private:
			static std::map<std::wstring, Resource*> mResources;
	};
}