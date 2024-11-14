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



	private:
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;
		
		// 플레이어
		GameObject mPlayer;
	};
}
	