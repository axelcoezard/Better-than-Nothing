#include "CKeyboardHandler.hpp"

namespace BetterThanNothing
{

	int CKeyboardHandler::m_Keys[KEYBOARD_KEY_COUNT] = {};

	CKeyboardHandler::CKeyboardHandler(void) {
		for (int i = 0; i < KEYBOARD_KEY_COUNT; i++) {
			m_Keys[i] = GLFW_RELEASE;
		}
	}

	CKeyboardHandler::~CKeyboardHandler(void) {}

	void CKeyboardHandler::UpdateKey(int key, int action) {
		CKeyboardHandler::m_Keys[key] = action;
	}

	void CKeyboardHandler::PressKey(int key) {
		CKeyboardHandler::m_Keys[key] = GLFW_PRESS;
	}

	void CKeyboardHandler::ReleaseKey(int key) {
		CKeyboardHandler::m_Keys[key] = GLFW_RELEASE;
	}

	bool CKeyboardHandler::IsKeyPressed(int key) {
		return CKeyboardHandler::m_Keys[key] == GLFW_PRESS || CKeyboardHandler::m_Keys[key] == GLFW_REPEAT;
	}
};
