
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CRenderer.hpp"
#include "Handlers/CKeyboardHandler.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new CWindow("better than nothing", 720, 720);
	auto pDevice = new CDevice(pWindow);
	auto pRenderer = new CRenderer(pWindow, pDevice);

	pRenderer->LoadPipeline(
		"main",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv");

	pRenderer->LoadModel(
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/metal.jpg");

	pRenderer->LoadModel(
		"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.png");

	pRenderer->LoadModel(
		"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.png");

	pRenderer->PrepareFrame();
	while (!pWindow->ShouldClose()) {
		pWindow->Poll();

		if (CKeyboardHandler::IsKeyPressed(GLFW_KEY_W)) {
			pRenderer->MoveCamera(-.001f, 0.0f, -.001f);
		}

		if (CKeyboardHandler::IsKeyPressed(GLFW_KEY_S)) {
			pRenderer->MoveCamera(.001f, 0.0f, .001f);
		}

		pRenderer->DrawFrame();
	}

	pDevice->Idle();

	delete pRenderer;
	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


