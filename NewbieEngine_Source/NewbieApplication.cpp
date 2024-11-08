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
		// main�� winProc �޼��� �������� ���� �� �� ���� �׷���
		// Render�� ������ ���� �� run���� ��������
		mPlayer.Render(mHdc);
	}
}
