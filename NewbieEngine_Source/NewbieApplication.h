#pragma once
namespace ya {
	class Application
	{

	public:
		void Initialize();
		void Run();
		
		void Updata();		// 먼저 업데이트
		void LateUpdate();	// 나중에 업데이트
		void Render();		// 그리는 건 전부 여기



	private:
	};
}
	