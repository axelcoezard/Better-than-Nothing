#include "Handlers/Input.hpp"

namespace BetterThanNothing
{

	int Input::m_Keys[KEYBOARD_KEY_COUNT] = {};

	f64 Input::m_MouseX = 0;
	f64 Input::m_MouseY = 0;
	f64 Input::m_LastMouseX = 0;
	f64 Input::m_LastMouseY = 0;

	f64 Input::m_MouseScroll = 0;
	int Input::m_Buttons[MOUSE_BUTTON_COUNT] = {};

	Input::Input(void)
	{
		for (int i = 0; i < KEYBOARD_KEY_COUNT; i++) {
			m_Keys[i] = GLFW_RELEASE;
		}
	}

	Input::~Input(void) {}

	void Input::UpdateKey(int key, int action)
	{
		Input::m_Keys[key] = action;
	}

	void Input::PressKey(int key)
	{
		Input::m_Keys[key] = GLFW_PRESS;
	}

	void Input::ReleaseKey(int key)
	{
		Input::m_Keys[key] = GLFW_RELEASE;
	}

	void Input::UpdateMouseButton(int button, int action)
	{
		Input::m_Buttons[button] = action;
	}

	void Input::PressMouseButton(int button)
	{
		Input::m_Buttons[button] = GLFW_PRESS;
	}

	void Input::ReleaseMouseButton(int button)
	{
		Input::m_Buttons[button] = GLFW_RELEASE;
	}

	void Input::UpdateMousePosition(f64 x, f64 y)
	{
		Input::m_LastMouseX = Input::m_MouseX;
		Input::m_LastMouseY = Input::m_MouseY;
		Input::m_MouseX = x;
		Input::m_MouseY = y;
	}

	glm::vec2 Input::GetMousePosition()
	{
		return glm::vec2(Input::m_MouseX, Input::m_MouseY);
	}

	glm::vec2 Input::GetLastMousePosition()
	{
		return glm::vec2(Input::m_LastMouseX, Input::m_LastMouseY);
	}

	glm::vec2 Input::GetMouseDelta()
	{
		return glm::vec2(Input::m_MouseX - Input::m_LastMouseX, Input::m_LastMouseY - Input::m_MouseY);
	}

	void Input::UpdateMouseScroll(f64 y)
	{
		Input::m_MouseScroll = y;
	}

	f64 Input::GetMouseScroll(void)
	{
		return Input::m_MouseScroll;
	}

	bool Input::IsKeyPressed(int key)
	{
		return Input::m_Keys[key] == GLFW_PRESS || Input::m_Keys[key] == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return Input::m_Buttons[button] == GLFW_PRESS || Input::m_Buttons[button] == GLFW_REPEAT;
	}
};
