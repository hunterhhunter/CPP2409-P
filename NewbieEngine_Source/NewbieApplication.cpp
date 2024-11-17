#include "NewbieApplication.h"
#include "NewbieInput.h"
#include "NewbieTime.h"
#include "NewbieSceneManager.h"

namespace newbie
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(NULL)
		, mBackBitmap(NULL)
	{

	}
	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		adjustWindowRect(hwnd, width, height);
		createBuffer(width, height);
		initializeEtc();

		SceneManager::Initialize();
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		// HWND는 Handle Window로 창을 컨트롤하는 객체
		// HDC는 Handle Device Context로 창에 렌더링할 때 사용
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height)
	{
		//윈도우 해상도에 맞는 백버퍼(도화지)생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		//백버퍼를 가르킬 DC생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::initializeEtc()
	{
		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run()
	{
		Updata();
		LateUpdate();
		Render();
	}

	void Application::clearRenderTarget()
	{
		// 1픽셀 키워서 선 안보이게 하기
		Rectangle(mBackHdc, -1, -1, 1610, 910);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		// source에서 dest로 복사
		BitBlt(dest, 0, 0, mWidth, mHeight
			, source, 0, 0, SRCCOPY);
	}

	void Application::Updata()
	{
		// 상태업데이트시 사용 (이동, 입력 등)
		// 11.13 - Input클래스로 입력 업데이트
		Input::Update();
		// 11.14 - TIme 클래스 Update
		Time::Update();
		
		// SceneManager가 Update
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		// Rendering 되는 함수 
		clearRenderTarget();

		// Time Rendering
		Time::Render(mBackHdc);

		// GameObject Render도 SceneManager가
		SceneManager::Render(mBackHdc);

		// BackBuffer에 있는걸 원본 Buffer에 복사
		copyRenderTarget(mBackHdc, mHdc);
	}
}
