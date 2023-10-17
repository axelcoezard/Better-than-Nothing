#pragma once

#define KEYBOARD_KEY_COUNT 1024

namespace BetterThanNothing
{
	struct CKeyboardHandler {
	protected:
		static int m_Keys[KEYBOARD_KEY_COUNT];

	public:
		CKeyboardHandler(void);
		~CKeyboardHandler(void);

		CKeyboardHandler(CKeyboardHandler&) = delete;
		void operator=(const CKeyboardHandler&) = delete;

		static void UpdateKey(int key, int action);
		static void PressKey(int key);
		static void ReleaseKey(int key);

		static bool IsKeyPressed(int key);
	};
};
