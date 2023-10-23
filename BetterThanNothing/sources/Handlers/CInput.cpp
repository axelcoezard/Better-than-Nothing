#include "CInput.hpp"

namespace BetterThanNothing
{

	int CInput::m_Keys[KEYBOARD_KEY_COUNT] = {};

	double CInput::m_MouseX = 0;
	double CInput::m_MouseY = 0;
	double CInput::m_LastMouseX = 0;
	double CInput::m_LastMouseY = 0;

	double CInput::m_MouseScroll = 0;
	int CInput::m_Buttons[MOUSE_BUTTON_COUNT] = {};

	CInput::CInput(void)
	{
		for (int i = 0; i < KEYBOARD_KEY_COUNT; i++) {
			m_Keys[i] = GLFW_RELEASE;
		}
	}

	CInput::~CInput(void) {}

	void CInput::UpdateKey(int key, int action)
	{
		CInput::m_Keys[key] = action;
	}

	void CInput::PressKey(int key)
	{
		CInput::m_Keys[key] = GLFW_PRESS;
	}

	void CInput::ReleaseKey(int key)
	{
		CInput::m_Keys[key] = GLFW_RELEASE;
	}

	void CInput::UpdateMouseButton(int button, int action)
	{
		CInput::m_Buttons[button] = action;
	}

	void CInput::PressMouseButton(int button)
	{
		CInput::m_Buttons[button] = GLFW_PRESS;
	}

	void CInput::ReleaseMouseButton(int button)
	{
		CInput::m_Buttons[button] = GLFW_RELEASE;
	}

	void CInput::UpdateMousePosition(double x, double y)
	{
		CInput::m_LastMouseX = CInput::m_MouseX;
		CInput::m_LastMouseY = CInput::m_MouseY;
		CInput::m_MouseX = x;
		CInput::m_MouseY = y;
	}

	glm::vec2 CInput::GetMousePosition()
	{
		return glm::vec2(CInput::m_MouseX, CInput::m_MouseY);
	}

	glm::vec2 CInput::GetLastMousePosition()
	{
		return glm::vec2(CInput::m_LastMouseX, CInput::m_LastMouseY);
	}

	glm::vec2 CInput::GetMouseDelta()
	{
		return glm::vec2(CInput::m_MouseX - CInput::m_LastMouseX, CInput::m_LastMouseY - CInput::m_MouseY);
	}

	void CInput::UpdateMouseScroll(double y)
	{
		CInput::m_MouseScroll = y;
	}

	double CInput::GetMouseScroll(void)
	{
		return CInput::m_MouseScroll;
	}

	bool CInput::IsKeyPressed(int key)
	{
		return CInput::m_Keys[key] == GLFW_PRESS || CInput::m_Keys[key] == GLFW_REPEAT;
	}

	bool CInput::IsMouseButtonPressed(int button)
	{
		return CInput::m_Buttons[button] == GLFW_PRESS || CInput::m_Buttons[button] == GLFW_REPEAT;
	}
};
