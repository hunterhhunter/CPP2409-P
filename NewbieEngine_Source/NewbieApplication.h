#pragma once
#include "NewbieGameObject.h"

namespace newbie {
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND mHwnd, UINT width, UINT height);
		void Run();
		
		void Updata();		// 먼저 업데이트
		void LateUpdate();	// 나중에 업데이트
		void Render();		// 그리는 건 전부 여기
		void Release();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC source, HDC dest);
		void adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void initializeEtc();

	private:
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;
		
		// 플레이어
		// std::vector<GameObject*> mGameObjects;
		
	};
}
	