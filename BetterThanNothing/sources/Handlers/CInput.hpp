#pragma once

#define KEYBOARD_KEY_COUNT 1024
#define MOUSE_BUTTON_COUNT 32

namespace BetterThanNothing
{
	struct CInput {
	protected:
		static int m_Keys[KEYBOARD_KEY_COUNT];

		static double m_MouseX, m_MouseY;
		static double m_MouseScroll;
		static int m_Buttons[MOUSE_BUTTON_COUNT];

	public:
		CInput(void);
		~CInput(void);

		CInput(CInput&) = delete;
		void operator=(const CInput&) = delete;

		static void UpdateKey(int key, int action);
		static void PressKey(int key);
		static void ReleaseKey(int key);

		static void UpdateMouseButton(int button, int action);
		static void PressMouseButton(int button);
		static void ReleaseMouseButton(int button);

		static void UpdateMousePosition(double x, double y);
		static void GetMousePosition(double& x, double& y);

		static void UpdateMouseScroll(double y);
		static double GetMouseScroll(void);

		static bool IsKeyPressed(int key);
		static bool IsMouseButtonPressed(int button);
	};
};
