#include "NewbieInput.h"

namespace newbie
{
	std::vector<Input::Key> Input::Keys = {};

	int ASCII[(UINT)eKeyCode::End] = {
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
	};

	void Input::Initialize()
	{
		createKeys();
	}

	void Input::Update()
	{
		for (size_t i = 0; i < Keys.size(); i++)
		{
			// 키가 눌리면
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{	
				// 눌린 키 찾기
				if (Keys[i].bPressed == true) // 과거에도 눌려있었을 때
					Keys[i].state = eKeyState::Pressed;
				else // 새로 누르는 상태
					Keys[i].state = eKeyState::Down;
				Keys[i].bPressed = true;
			}
			else // 키가 안눌림
			{
				if (Keys[i].bPressed = true) // 이전에 누르다가 놓은 상태
					Keys[i].state = eKeyState::Up;
				else // 아예 눌리지 않은 상태
					Keys[i].state = eKeyState::None;
				Keys[i].bPressed = false;
			}
		}
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
		if (isKeyDown(key.keyCode))
		{
			updateKeyDown(key);
		}
		else
		{
			updateKeyUp(key);
		}
	}

	bool Input::isKeyDown(eKeyCode code)
	{
		return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
	}

	void Input::updateKeyDown(Input::Key& key)
	{
		if (key.bPressed == true)
			key.state = eKeyState::Pressed;
		key.bPressed = true;
	}

	void Input::updateKeyUp(Input::Key& key)
	{
		if (key.bPressed == true)
			key.state = eKeyState::Up;
		else
			key.state = eKeyState::None;

		key.bPressed = false;
	}
}