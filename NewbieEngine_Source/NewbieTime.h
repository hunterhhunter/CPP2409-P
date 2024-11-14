#pragma once
#include "Commoninclude.h"

namespace newbie
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static float DeltaTime() { return DeltaTimeValue; }
	
	private:
		static LARGE_INTEGER CpuFrequency;
		static LARGE_INTEGER PrevFrequency;
		static LARGE_INTEGER CurrentFrequency;
		// DeltaTimeValue는 프레임간의 시간을 기록 -> 프레임간 간격이 얼마든 일정한 렌더 가능
		static float DeltaTimeValue;

	};
}

