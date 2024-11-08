#include "NewbieApplication.h"

namespace newbie
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mSpeed(0.0f)
	{

	}
	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
	}

	void Application::Run()
	{
		Updata();
		LateUpdate();
		Render();
	}

	void Application::Updata()
	{
		mPlayer.Update();
	}

	void Application::LateUpdate()
	{

	}

	void Application::Render()
	{
		// main의 winProc 메서드 내에서는 실행 시 한 번만 그려짐
		// Render로 변경한 순간 매 run마다 렌더링됨
		mPlayer.Render(mHdc);
	}
}
