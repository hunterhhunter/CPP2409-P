#include "NewbieInput.h"
#include "NewbieApplication.h"

extern newbie::Application application;

namespace newbie
{
	std::vector<Input::Key> Input::Keys = {};
	math::Vector2 Input::mMousePosition = math::Vector2::Zero;

	int ASCII[(UINT)eKeyCode::End] = {
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON,
	};

	void Input::Initialize()
	{
		createKeys();
	}

	void Input::Update()
	{
		updateKeys();
	}

	void Input::createKeys() {
		// vector로 mKeys의 배열을 만들고 각 자판마다의 key클래스를 만들어
		// mKeys에 push함으로 각 키를 객체화해 관리를 쉽게 만듦
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {
			Key key = {};
			key.bPressed = false;
			key.state = eKeyState::None;
			key.keyCode = (eKeyCode)i;

			Keys.push_back(key);
		}
	}

	void Input::updateKeys() 
	{
		std::for_each(Keys.begin(), Keys.end(),
			[](Key& key) -> void
			{
				updateKey(key);
			});
	}
	
	void Input::updateKey(Input::Key& key) 
	{
		// 창이 포커싱 되었을 때
		if (GetFocus())
		{
			// 키 눌렸는지 확인 및 업데이트
			if (isKeyDown(key.keyCode))
				updateKeyDown(key);
			else
				updateKeyUp(key);
			
			// 마우스 포지션 가져오기
			getMousePositionByWindow();
		}
		else
		{
			clearKeys();
		}
	}

	bool Input::isKeyDown(eKeyCode code)
	{
		// 키가 눌렸는지 확인
		return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
	}

	void Input::updateKeyDown(Input::Key& key)
	{
		// 눌려있는지 확인 후 업데이트
		if (key.bPressed == true)
			key.state = eKeyState::Pressed;
		else
			key.state = eKeyState::Down;
		key.bPressed = true;
	}

	void Input::updateKeyUp(Input::Key& key)
	{
		// 눌려있다가 떼지는 경우
		if (key.bPressed == true)
			key.state = eKeyState::Up;
		else
			key.state = eKeyState::None;

		key.bPressed = false;
	}

	void Input::getMousePositionByWindow()
	{
		// 창에서 마우스의 위치를 가져오는 함수
		// 마우스 위치를 저장할 POINT 객체
		POINT mousePos = {};
		// 화면 전체 좌표계에서의 마우스 위치 반환
		GetCursorPos(&mousePos);
		// 현재 application의 Hwnd(Window)의 상대좌표로 변환
		ScreenToClient(application.GetHwnd(), &mousePos);

		mMousePosition.x = mousePos.x;
		mMousePosition.y = mousePos.y;
	}

	void Input::clearKeys()
	{
		for (Key& key : Keys)
		{
			if (key.state == eKeyState::Down || key.state == eKeyState::Pressed)
				key.state = eKeyState::Up;
			else if (key.state == eKeyState::Up)
				key.state = eKeyState::None;

			key.bPressed = false;
		}
	}
}