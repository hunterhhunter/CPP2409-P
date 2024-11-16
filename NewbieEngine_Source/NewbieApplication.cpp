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
		// HWND는 Handle Window로 창을 컨트롤하는 객체
		// HDC는 Handle Device Context로 창에 렌더링할 때 사용
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
		// 창 크기 변경을 위한 Init 변경
		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(mHwnd, true);

		// 더블버퍼링 구현
		// 윈도우 해상도에 맞는 백버퍼 생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		// 백버퍼를 가리키는 DC 만들기
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);

		// 11.14 Object vector화
		// for (size_t i=0; i< 100; i++)
		// {
		// 	GameObject* gameObj = new GameObject();
		//	gameObj->SetPosition(rand() % 1600, rand() % 900);
		//	mGameObjects.push_back(gameObj);
		//}
		// 11.14 SceneManager로 Object 관리
		SceneManager::Initialize();

		// 11.13 - Input클래스로 입력 처리
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
		Rectangle(mBackHdc, 0, 0, 1610, 910);
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

	}

	void Application::Render()
	{
		// Rendering 되는 함수 
		clearRenderTarget();

		// Time Rendering
		Time::Render(mBackHdc);

		// for (size_t i = 0; i < mGameObjects.size(); i++)
		// {
		//	mGameObjects[i]->Render(mHdc);
		// }
		// GameObject Render도 SceneManager가
		SceneManager::Render();

		// BackBuffer에 있는걸 원본 Buffer에 복사
		copyRenderTarget(mBackHdc, mHdc);
	}
}
