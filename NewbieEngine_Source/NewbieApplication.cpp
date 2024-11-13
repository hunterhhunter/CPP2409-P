#include "NewbieApplication.h"
#include "NewbieInput.h"

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
		// 11.13 - Input클래스로 입력 처리
		Input::Initialize();
	}

	void Application::Run()
	{
		Updata();
		LateUpdate();
		Render();
	}

	void Application::Updata()
	{
		// 상태업데이트시 사용 (이동, 입력 등)
		// 11.13 - Input클래스로 입력 업데이트
		Input::Update();
		mPlayer.Update();
	}

	void Application::LateUpdate()
	{

	}

	void Application::Render()
	{
		// Rendering 되는 함수           
		mPlayer.Render(mHdc);
	}
}
