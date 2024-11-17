#include "NewbieTime.h"

namespace newbie
{
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;

	void Time::Initialize()
	{
		// cpu 고유 clock
		QueryPerformanceFrequency(&CpuFrequency);

		// 프로그램 시작 시 clock
		QueryPerformanceCounter(&PrevFrequency);
	}
	
	void Time::Update()
	{
		// 현시점 타이머 값을 가져옴
		QueryPerformanceCounter(&CurrentFrequency);
		// 이전 시점과 현 시점의 카운터 차이를 계산
		float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
		// 델타 타임 계산
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);
		// 현재 값을 이전의 값으로 업데이트
		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;

		time += DeltaTimeValue;

		// 초당 프레임 계산
		float fps = 1.0f / DeltaTimeValue;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"Time : %d", (int)fps);
		int len = wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);
	}
}
